#include <gtest/gtest.h>

#include <etk/widgets/label.h>
#include <etk/application.h>

#include <etk/widgets/scene.h>

TEST(LabelTest, Constructor) {
	auto label = std::make_shared<etk::Label>();
}

TEST(LabelTest, SetText) {
	auto label = std::make_shared<etk::Label>();
	label->SetText(L"Hello");
}

TEST(LabelTest, SetTextWidthHeightOpenGL) {
	auto label = std::make_shared<etk::Label>();
	label->SetText(L"Hello");
	auto app = std::make_shared<etk::Application>();
	auto win = app->CreateAppWindow("hello world");
	auto scene = std::make_shared<etk::Scene>(L"MAIN");
	win.lock()->SetScene(scene);
	scene->SetWidget(L"LABEL", L"MAIN", label);
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
	ASSERT_GT(label->GetExternalHeight(), 0.0f);
	ASSERT_GT(label->GetExternalWidth(), 0.0f);
}


