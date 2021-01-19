#include <etk/application.h>
#include <etk/window.h>

int main(int argc, char** argv)
{
	etk::Application app;
	etk::Window win;
	app.Init(argc, argv);
	return app.Run();
}
