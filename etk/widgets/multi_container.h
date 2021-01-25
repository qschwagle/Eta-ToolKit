#pragma once

#include "widget.h"
#include <vector>

namespace etk {
class MultiContainer : public etk::Widget
{
public:
	virtual void AddWidget(std::shared_ptr<Widget> widget)
	{
		mWidgetList.push_back(widget);
		widget->SetDrawableFactory(GetDrawableFactory());
		if (IsInitialized()) widget->Init();
	}

	virtual void ClearWidgets(std::shared_ptr<Widget> widget)
	{
		mWidgetList.clear();
	}

	void Draw(const glm::vec2& eye) override
	{
		for(auto i: mWidgetList) i->Draw(eye + GetEye());
	}

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory) override {
		Widget::SetDrawableFactory(factory);
		for(auto i: mWidgetList) i->SetDrawableFactory(factory);
	}

	void Init() override {
		for (auto& i : mWidgetList) i->Init();
		etk::Widget::Init();
	}

	bool OnScroll(const glm::vec2 point, float xOffset, float yOffset)
	{
		if (HitInsideBox(point)) {
			for (auto& i : mWidgetList) {
				if (i->OnScroll(point, xOffset, yOffset)) {
					return true;
				}
			}
			return etk::Widget::OnScroll(point, xOffset, yOffset);
		}
	}


protected:
	virtual void UpdateChildrenPositions() {};

	std::vector<std::shared_ptr<etk::Widget>>& GetWidgetList() {
		return mWidgetList;
	}

private:
	std::vector<std::shared_ptr<etk::Widget>> mWidgetList;
};
}