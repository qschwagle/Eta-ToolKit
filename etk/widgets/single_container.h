#pragma once

#include "widget.h"

namespace etk {
class SingleContainer : public etk::Widget {
public:
	void Draw() override
	{
		if(mWidget) mWidget->Draw();
	}
	void SetWidget(std::shared_ptr<Widget> widget)
	{
		mWidget = widget;
		mWidget->SetDrawableFactory(GetDrawableFactory());
	}

	void ClearWidget(std::shared_ptr<Widget> widget)
	{
		mWidget = nullptr;
	}

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory) override {
		Widget::SetDrawableFactory(factory);
		if (mWidget) mWidget->SetDrawableFactory(factory);
	}

protected:
	std::shared_ptr<Widget> GetWidget() {
		return mWidget;
	}
private:
	std::shared_ptr<Widget> mWidget;
};
}