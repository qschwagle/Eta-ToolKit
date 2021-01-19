#include <gtest/gtest.h>

#include <etk/application.h>

TEST(ApplicationTest, Constructor) {
	etk::Application app;
}

TEST(ApplicationTest, SimpleRun) {
	etk::Application app;
	char* hello[1] = { "app" };
	app.Init(1, hello);
	ASSERT_EQ(0, app.Run());
}
