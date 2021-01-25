#pragma once

#include "widget.h"

namespace etk {
class SingleContainer : public etk::Widget {
public:
	void Draw(const glm::vec2& eye) override
	{
		if(mWidget) mWidget->Draw(eye + GetEye());
	}
	void SetWidget(std::shared_ptr<Widget> widget)
	{
		mWidget = widget;
		mWidget->SetDrawableFactory(GetDrawableFactory());
		if (IsInitialized()) mWidget->Init();
	}

	void ClearWidget(std::shared_ptr<Widget> widget)
	{
		mWidget = nullptr;
	}

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory) override {
		Widget::SetDrawableFactory(factory);
		if (mWidget) mWidget->SetDrawableFactory(factory);
	}

	void Init() override;

	bool OnScroll(const glm::vec2 point, float xOffset, float yOffset) override {
		if (HitInsideBox(point)) {
			if (!mWidget->OnScroll(point, xOffset, yOffset)) {
				return etk::Widget::OnScroll(point, xOffset, yOffset);
			}
			return true;
		}
	}

protected:
	std::shared_ptr<Widget> GetWidget() {
		return mWidget;
	}
private:
	std::shared_ptr<Widget> mWidget;
};
}