#include <gtest/gtest.h>

#include <etk/application.h>

#include <etk/run_on_ui_thread.h>

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
	int id = app->CreateWindow("hello world");
	char* hello[1] = { "app" };
	auto thread = etk::RunOnUIThread::GetInstance();
	auto count = std::make_shared<int>(0);
	thread->ScheduleFunc([count, id, app]()->bool {
		if (*count != 2) {
			(*count)++;
			return true;
		}
		else {
			etk::Window* win = app->GetWindow(id);
			if (win) win->MarkToClose();
			return false;
		}
		});
	app->Init(1, hello);
	ASSERT_EQ(0, app->Run());
	ASSERT_EQ(*count, 2);
}
