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

#include <locale>
#include <codecvt>

#include<vector>

std::vector<std::wstring> supported_image_types = {L"png", L"jpeg", L"jpg", L"bmp"};

int main(int argc, char** argv)
{
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

	auto imageLayout = std::make_shared<etk::LinearLayout>();
	imageLayout->SetScroller(std::make_unique<etk::LinearLayout::VerticalScroller>());
	auto directoryChooserButton = std::make_shared<etk::Button>();
	directoryChooserButton->SetText(L"Choose Directory");
	scene->SetWidget(L"CHOOSE_DIRECTORY_BUTTON", L"MAIN_LAYOUT", directoryChooserButton);

	std::weak_ptr<etk::LinearLayout> imageLayoutWeak = imageLayout;

	scene->SetWidget(L"IMAGE_LAYOUT", L"MAIN_LAYOUT", std::static_pointer_cast<etk::MultiContainer>(imageLayout));

	// initialize the app
	app.Init(argc, argv);

	// run the app
	int ret = app.Run();

	CoUninitialize();
	return ret;
}
