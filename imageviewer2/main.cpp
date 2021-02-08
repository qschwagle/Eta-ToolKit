#include <etk/application.h>
#include <etk/window.h>
#include <etk/widgets/scene.h>
#include <etk/color.h>
#include <etk/widgets/button.h>
#include <etk/widgets/image.h>
#include <etk/widgets/label.h>
#include <etk/widgets/linear_layout.h>

#include <windows.h>
#include <crtdbg.h>
#include <ShObjIdl.h>

#include<vector>

#include "list_adapter.h"

std::vector<std::wstring> supported_image_types = {L"png", L"jpeg", L"jpg", L"bmp"};

int main(int argc, char** argv)
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	// The Application itself
	etk::Application app;

	// create the window
	auto window = app.CreateAppWindow("Image Viewer").lock();

	// set the background color
	window->SetColor(etk::colors::PURPLE);

	// create a scene
	auto scene = std::make_shared<etk::Scene>(L"MAIN_SCENE");
	window->SetScene(scene);

	auto mainLayout = std::make_shared<etk::LinearLayout>();
	scene->SetWidget(L"MAIN_LAYOUT", L"MAIN_SCENE", std::static_pointer_cast<etk::MultiContainer>(mainLayout));

	std::shared_ptr<std::vector<std::wstring>> fileList = std::make_shared<std::vector<std::wstring>>();

	ListAdapter*  adapter = new ListAdapter(0, fileList);

	auto imageList = std::make_shared<etk::ListView<std::wstring>>();
	imageList->SetScroller(std::make_unique<etk::LinearLayout::VerticalScroller>());
	imageList->SetModel(adapter);

	auto directoryChooserButton = std::make_shared<etk::Button>();
	directoryChooserButton->SetText(L"Choose Directory");
	scene->SetWidget(L"CHOOSE_DIRECTORY_BUTTON", L"MAIN_LAYOUT", directoryChooserButton);
	scene->SetWidget(L"IMAGE_LIST", L"MAIN_LAYOUT", std::static_pointer_cast<etk::Widget>(imageList));

	directoryChooserButton->SetLeftClickCallback(std::make_unique<std::function<void()>>([&fileList]() {
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
