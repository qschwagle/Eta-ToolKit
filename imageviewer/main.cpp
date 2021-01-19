#include <etk/application.h>

int main(int argc, char** argv)
{
	etk::Application app;
	app.Init(argc, argv);
	return app.Run();
}
