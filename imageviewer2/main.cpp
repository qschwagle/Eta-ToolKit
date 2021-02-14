#include <etk/application.h>
#include <etk/window.h>
#include <etk/widgets/scene.h>
#include <etk/color.h>
#include <etk/widgets/button.h>
#include <etk/widgets/image.h>
#include <etk/widgets/label.h>
#include <etk/widgets/linear_layout.h>
#include <etk/widgets/scene_builder_func.h>

#include <windows.h>
#include <crtdbg.h>
#include <ShObjIdl.h>

#include<vector>

#include "list_adapter.h"

std::vector<std::wstring> supported_image_types = {L"png", L"jpeg", L"jpg", L"bmp"};

/// <summary>
/// Builds the scene used as List Items. Passed to the ListView
/// </summary>
/// <returns>List View Item Scene</returns>
std::shared_ptr<etk::Scene> CreateSceneBuilder() {
	auto scene = std::make_shared<etk::Scene>(L"ITEM_SCENE");
	auto layout = std::make_shared<etk::LinearLayout>();
	auto title = std::make_shared<etk::Label>();
	title->SetMargin(glm::vec4(0.0f, 0.0f, 10.0f, 0.0f));
	title->SetTextColor(etk::colors::RED);
	title->SetFontSize(etk::PointUnit(16));
	auto image = std::make_shared <etk::Image>();

	scene->SetWidget(L"LAYOUT", L"ITEM_SCENE", std::dynamic_pointer_cast<etk::MultiContainer>(layout));
	scene->SetWidget(L"TITLE", L"LAYOUT", title);
	scene->SetWidget(L"IMAGE", L"LAYOUT", image);

	return scene;
}

int main(int argc, char** argv)
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	// The Application itself
	etk::Application app;

	// create the window
	auto window = app.CreateAppWindow("Image Viewer").lock();

	// set the background color
	window->SetColor(etk::colors::WHITE);

	// create the main scene
	auto scene = std::make_shared<etk::Scene>(L"MAIN_SCENE");
	
	// set the main scene
	window->SetScene(scene);

	// main layout used to hold the configuration buttons and ListView 
	auto mainLayout = std::make_shared<etk::LinearLayout>();

	// Insert the listview into the main scene
	scene->SetWidget(L"MAIN_LAYOUT", L"MAIN_SCENE", std::static_pointer_cast<etk::MultiContainer>(mainLayout));

	// model containing a list of file paths
	std::shared_ptr<std::vector<std::wstring>> fileList = std::make_shared<std::vector<std::wstring>>();

	// adapter to map the list of file paths to ListView items
	ListAdapter* adapter = new ListAdapter(0, fileList);

	// List View 
	auto imageList = std::make_shared<etk::ListView<std::wstring>>();

	// List View needs to be scrollable
	imageList->SetScroller(std::make_unique<etk::LinearLayout::VerticalScroller>());

	// set the model adapter
	imageList->SetModel(adapter);

	// set the scene builder
	imageList->SetSceneBuilder(std::make_shared<etk::SceneBuilderFunction>(CreateSceneBuilder));

	// button to get the folder picker
	auto directoryChooserButton = std::make_shared<etk::Button>();

	// button text
	directoryChooserButton->SetText(L"Choose Directory");

	// set the margin in pixels
	directoryChooserButton->SetMargin(glm::vec4(5.0f, 5.0f, 5.0f, 5.0f));

	directoryChooserButton->SetTextColor(etk::colors::BLUE);
	directoryChooserButton->SetFontSize(etk::PointUnit(24));

	// set the button inside the layout
	scene->SetWidget(L"CHOOSE_DIRECTORY_BUTTON", L"MAIN_LAYOUT", directoryChooserButton);

	// insert the image list
	scene->SetWidget(L"IMAGE_LIST", L"MAIN_LAYOUT", std::static_pointer_cast<etk::Widget>(imageList));

	// button callback for folder picker
	directoryChooserButton->SetLeftClickCallback(std::make_unique<std::function<void()>>([&fileList, adapter]() {
		IFileOpenDialog* pFileOpen;
		HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr)) {
			pFileOpen->SetOptions(FOS_PICKFOLDERS);
			hr = pFileOpen->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					std::wstring new_path;
					if (SUCCEEDED(hr)) {
						for (int i = 0; pszFilePath[i] != 0; ++i) {
							new_path.push_back(pszFilePath[i]);
						}
						CoTaskMemFree(pszFilePath);
					}
                    auto& directory_path = new_path;
                    if (!directory_path.size()) {
                        return false;
                    }
                    std::wstring directory_file_retrievel = directory_path;
                    directory_file_retrievel.append(L"\\*");
                    WIN32_FIND_DATAW FindFileData;
                    HANDLE hFind = FindFirstFileW(directory_file_retrievel.c_str(), &FindFileData);
                    do
                    {
                        std::wstring name = std::wstring(FindFileData.cFileName);
                        if (name.compare(L".") == 0) continue;
                        if (name.compare(L"..") == 0) continue;
                        std::wstring reverse_name = name;
                        std::reverse(reverse_name.begin(), reverse_name.end());
                        std::wstring ending;
                        for (auto i = reverse_name.begin(); i != reverse_name.end() && (*i) != '.'; ++i)
                        {
                            ending.push_back(*i);
                        }
                        std::reverse(ending.begin(), ending.end());
                        bool should_add = false;
                        for (std::vector<std::wstring>::const_iterator i = supported_image_types.cbegin(); !should_add && i != supported_image_types.cend(); ++i)
                        {
                            if (i->compare(ending) == 0) {
                                should_add = true;
                            }
                        }
                        if (!should_add) continue;
                        std::wstring hack;
                        for (auto& i : directory_path + L"\\" + name) {
                            hack.push_back(static_cast<char>(i));
                        }
						fileList->push_back(hack);

						// notify the adapter that the data structure has changed
						adapter->Notify();
                    } while (FindNextFileW(hFind, &FindFileData) != 0);
				}
				pItem->Release();
			}
		}
		pFileOpen->Release();
	}));

	// initialize the app
	app.Init(argc, argv);

	// run the app
	int ret = app.Run();

	CoUninitialize();
	return ret;
}
