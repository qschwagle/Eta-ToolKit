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

std::vector<std::wstring> supported_image_types = {L"png", L"jpeg", L"jpg", L"bmp"};

int main(int argc, char** argv)
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	// The Application itself
	etk::Application app;

	// create the window
	int id = app.CreateAppWindow("Image Viewer");
	auto window = app.GetWindow(id);

	// set the background color
	window->SetColor(etk::colors::PURPLE);

	// create a scene
	auto scene = std::make_shared<etk::Scene>(L"MAIN_SCENE");
	window->SetScene(scene);

	auto mainLayout = std::make_shared<etk::LinearLayout>();
	scene->SetWidget(L"MAIN_LAYOUT", L"MAIN_SCENE", std::static_pointer_cast<etk::MultiContainer>(mainLayout));

	auto imageLayout = std::make_shared<etk::LinearLayout>();
	imageLayout->SetScroller(std::make_unique<etk::LinearLayout::VerticalScroller>());
	auto directoryChooserButton = std::make_shared<etk::Button>();
	directoryChooserButton->SetText(L"Choose Directory");
	scene->SetWidget(L"CHOOSE_DIRECTORY_BUTTON", L"MAIN_LAYOUT", directoryChooserButton);

	std::weak_ptr<etk::LinearLayout> imageLayoutWeak = imageLayout;

	directoryChooserButton->SetLeftClickCallback(std::make_unique<std::function<void()>>([imageLayoutWeak, window]() {
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
					window->ScheduleFunc([imageLayoutWeak, new_path]() ->bool {
						auto imagesLayout = imageLayoutWeak.lock();
                        imagesLayout->ClearWidgets();
                        auto& directory_path = new_path;
                        auto& container = imagesLayout;
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
                            auto image = std::make_shared<etk::Image>();
                            std::wstring hack;
                            for (auto& i : directory_path + L"\\" + name) {
                                hack.push_back(static_cast<char>(i));
                            }
                            image->Load(hack);
                            //image->SetSizeSettingWidth(QSWidget::SizeSetting::OWNER);
                            //image->SetSizeSettingHeight(QSWidget::SizeSetting::OWNER);
                            //image->SetAlignment(QSImage::Alignment::CENTER);
                            //image->SetImageScaling(QSImage::ImageScaling::SCALING);
                            auto title = std::make_shared<etk::Label>();
                            std::string title_string;
                            title->SetText(name);
                            //title->SetFontSize(48);
                            container->AddWidget(title);
                            container->AddWidget(image);
                            //title->SetSizeSettingWidth(QSWidget::SizeSetting::OWNER);
                            //title->SetAlignment(QSLabel::TextAlignment::CENTER);
                        } while (FindNextFileW(hFind, &FindFileData) != 0);
                        //mWindow->LayoutChanged();
						return false;
					});
				}
				pItem->Release();
			}
		}
		pFileOpen->Release();
	}));

	scene->SetWidget(L"IMAGE_LAYOUT", L"MAIN_LAYOUT", std::static_pointer_cast<etk::MultiContainer>(imageLayout));

	// initialize the app
	app.Init(argc, argv);

	// run the app
	int ret = app.Run();

	CoUninitialize();
	return ret;
}
