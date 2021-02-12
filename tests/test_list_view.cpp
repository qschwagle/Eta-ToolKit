#include <gtest/gtest.h>

#include <etk/application.h>
#include <etk/widgets/scene.h>

#include <etk/widgets/list_view.h>

#include <memory>


TEST(ListView, Constructor) {
	auto listView = std::make_shared<etk::ListView<std::string>>();
}

TEST(ListView, FactoryInit) {
	auto listView = std::make_shared<etk::ListView<std::string>>();
	auto app = std::make_shared<etk::Application>();
	auto window = app->CreateAppWindow();
	auto scene = std::make_shared<etk::Scene>(L"MAIN_SCENE");
	window.lock()->SetScene(scene);
	scene->SetWidget(L"LIST_VIEW", L"MAIN_SCENE", listView);

	char* name[1] = { "Hello" };

	app->Init(1, name);
}

TEST(ListView, Adapter) {

}