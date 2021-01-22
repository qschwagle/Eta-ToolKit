#include <etk/application.h>
#include <etk/window.h>
#include <etk/scene.h>
#include <etk/color.h>
#include <etk/button.h>

int main(int argc, char** argv)
{
	// The Application itself
	etk::Application app;

	// create the window
	int id = app.CreateWindow("Image Viewer");
	auto window = app.GetWindow(id);

	// set the background color
	window->SetColor(etk::colors::PURPLE);

	// create a scene
	auto scene = std::make_shared<etk::Scene>(L"Main");
	window->SetScene(scene);

	// Add a button to the scene
	auto button = std::make_shared<etk::Button>();
	scene->SetWidget(L"SimpleButton", L"Main", button);

	// initialize the app
	app.Init(argc, argv);

	// run the app
	return app.Run();
}
