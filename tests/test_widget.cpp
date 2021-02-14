#include <gtest/gtest.h>

#include <etk/widgets/widget.h>


TEST(Widget, Constructor) {
	auto label = std::make_shared<etk::Widget>();
	auto owner = etk::GetOwner(*label);
	ASSERT_TRUE(owner.expired());
	ASSERT_EQ(label->GetBackgroundColor(), etk::colors::NONE);
}

TEST(Widget, MarginSetterGetter) {
	auto label = std::make_shared<etk::Widget>();
	glm::vec4 m{ 1.0f, 2.0f, 3.0f, 4.0f };
	label->SetMargin(m);
	auto g = label->GetMargin();
	ASSERT_FLOAT_EQ(g.x, 1.0f);
	ASSERT_FLOAT_EQ(g.y, 2.0f);	
	ASSERT_FLOAT_EQ(g.z, 3.0f);
	ASSERT_FLOAT_EQ(g.w, 4.0f);	
}

TEST(Widget, PaddingSetterGetter) {
	auto label = std::make_shared<etk::Widget>();
	glm::vec4 p{ 1.0f, 2.0f, 3.0f, 4.0f };
	label->SetPadding(p);
	auto g = label->GetPadding();
	ASSERT_FLOAT_EQ(g.x, 1.0f);
	ASSERT_FLOAT_EQ(g.y, 2.0f);	
	ASSERT_FLOAT_EQ(g.z, 3.0f);
	ASSERT_FLOAT_EQ(g.w, 4.0f);	
}

TEST(Widget, WidthHeightSetterGetter) {
	auto label = std::make_shared<etk::Widget>();
	label->SetInternalWidth(100);
	label->SetInternalHeight(100);

	ASSERT_EQ(label->GetExternalWidth(), 100);
	ASSERT_EQ(label->GetExternalHeight(), 100);
}

