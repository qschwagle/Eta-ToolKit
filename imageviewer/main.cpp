#include <etk/application.h>
#include <etk/window.h>
#include <etk/scene.h>
#include <etk/color.h>
#include <etk/button.h>

int main(int argc, char** argv)
{
	etk::Application app;
	int id = app.CreateWindow("Image Viewer");
	auto window = app.GetWindow(id);
	window->SetColor(etk::colors::PURPLE);
	auto scene = std::make_shared<etk::Scene>(L"Main");
	window->SetScene(scene);
	auto button = std::make_shared<etk::Button>();
	scene->SetWidget(L"SimpleButton", L"Main", button);
	app.Init(argc, argv);
	return app.Run();
}
