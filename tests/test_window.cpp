#include <gtest/gtest.h>

#include <etk/window.h>
#include <etk/color.h>

#include <etk/widgets/scene.h>



TEST(WindowTest, Constructor) {
	etk::Window win(0);
	ASSERT_EQ(etk::colors::WHITE, win.GetColor());
}

TEST(WindowTest, BackgroundColor) {
	etk::Window win(0);
	win.SetColor(etk::colors::BLACK);
	ASSERT_EQ(etk::colors::BLACK, win.GetColor());
}

TEST(WindowTest, SetScene) {
	auto win = std::make_shared<etk::Window>(0);
	auto i = win->GetScene().operator bool();
	ASSERT_EQ(i, false);
	auto scene = std::make_shared<etk::Scene>(L"ID");
	win->SetScene(scene);
	ASSERT_EQ(win->GetScene().get(), scene.get());
}
