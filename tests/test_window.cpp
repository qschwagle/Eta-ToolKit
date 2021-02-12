#include <gtest/gtest.h>

#include <etk/window.h>
#include <etk/color.h>

TEST(WindowTest, Constructor) {
	etk::Window win(0);
	ASSERT_EQ(etk::colors::WHITE, win.GetColor());
}

TEST(WindowTest, BackgroundColor) {
	etk::Window win(0);
	win.SetColor(etk::colors::BLACK);
	ASSERT_EQ(etk::colors::BLACK, win.GetColor());
}
