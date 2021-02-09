#include <gtest/gtest.h>

#include <etk/application.h>

#include <etk/renderer/generic/ui_thread_scheduler.h>

#include <memory>

TEST(ApplicationTest, Constructor) {
	etk::Application app;
}

TEST(ApplicationTest, SimpleRun) {
	etk::Application app;
	char* hello[1] = { "app" };
	app.Init(1, hello);
	ASSERT_EQ(0, app.Run());
}

TEST(ApplicationTest, CreateWindow) {
	auto app = std::make_shared<etk::Application>();
	auto win = app->CreateAppWindow("hello world");
	char* hello[1] = { "app" };
	auto count = std::make_shared<int>(0);
	win.lock()->ScheduleFunc([count, win, app]()->bool {
		if (*count != 2) {
			(*count)++;
			return true;
		}
		else {
			if (!win.expired()) win.lock()->MarkToClose();
			return false;
		}
		});
	app->Init(1, hello);
	ASSERT_EQ(0, app->Run());
	ASSERT_EQ(*count, 2);
}
