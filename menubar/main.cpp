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
#include<iostream>

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

	auto menuBar = std::make_shared<etk::LinearLayout>();
	menuBar->SetDirection(etk::LinearLayout::Direction::HORIZONTAL);
	scene->SetWidget(L"MENU_BAR", L"MAIN_LAYOUT", std::static_pointer_cast<etk::MultiContainer>(menuBar));

	auto fileButton = std::make_shared<etk::Button>();
	fileButton->SetText(L"File");
	fileButton->SetBackgroundColor(etk::colors::NONE);
	fileButton->SetMargin(glm::vec4(0.0f, 20.0f, 0.0f, 20.0f));
	fileButton->SetPadding(glm::vec4(0.0f, 20.0f, 0.0f, 0.0f));
	fileButton->SetLeftClickCallback(std::make_unique<std::function<void()>>([]() {
		std::cout << "File Button Click" << std::endl;
	}));
	scene->SetWidget(L"FILE_BUTTON", L"MENU_BAR", fileButton);

	auto editButton = std::make_shared<etk::Button>();
	editButton->SetText(L"Edit");
	editButton->SetBackgroundColor(etk::colors::NONE);
	editButton->SetMargin(glm::vec4(0.0f, 20.0f, 0.0f, 20.0f));
	editButton->SetPadding(glm::vec4(0.0f, 20.0f, 0.0f, 0.0f));
	editButton->SetLeftClickCallback(std::make_unique<std::function<void()>>([]() {
		std::cout << "Edit Button Click" << std::endl;
	}));
	scene->SetWidget(L"EDIT_BUTTON", L"MENU_BAR", editButton);

	auto viewButton = std::make_shared<etk::Button>();
	viewButton->SetText(L"View");
	viewButton->SetMargin(glm::vec4(0.0f, 20.0f, 0.0f, 20.0f));
	viewButton->SetBackgroundColor(etk::colors::NONE);
	viewButton->SetLeftClickCallback(std::make_unique<std::function<void()>>([]() {
		std::cout << "View Button Click" << std::endl;
	}));
	scene->SetWidget(L"VIEW_BUTTON", L"MENU_BAR", viewButton);

	// initialize the app
	app.Init(argc, argv);

	// run the app
	int ret = app.Run();

	CoUninitialize();
	return ret;
}
