#pragma once

#include "widget.h"
#include <vector>

namespace etk {
class MultiContainer : public etk::Widget
{
public:
	void AddWidget(std::shared_ptr<Widget> widget)
	{
		mWidgetList.push_back(widget);
		widget->SetDrawableFactory(GetDrawableFactory());
	}

	void ClearWidgets(std::shared_ptr<Widget> widget)
	{
		mWidgetList.clear();
	}

	void Draw() override
	{
		for(auto i: mWidgetList) i->Draw();
	}

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory) override {
		Widget::SetDrawableFactory(factory);
		for(auto i: mWidgetList) i->SetDrawableFactory(factory);
	}

private:
	std::vector<std::shared_ptr<etk::Widget>> mWidgetList;
};
}