#include <etk/application.h>
#include <etk/window.h>

#include <etk/color.h>

int main(int argc, char** argv)
{
	etk::Application app;
	int id = app.CreateWindow("Image Viewer");
	auto window = app.GetWindow(id);
	window->SetColor(etk::colors::PURPLE);
	app.Init(argc, argv);
	return app.Run();
}
