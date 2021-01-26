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
		widget->SetOwner(shared_from_this());
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
			if (!mWidget->OnScroll(GetEye()+point, xOffset, yOffset)) {
				return etk::Widget::OnScroll(point, xOffset, yOffset);
			}
			return true;
		}
	}

	bool OnLeftClick(float x, float y) override {
		if (HitInsideBox(glm::vec2{ x,y })) {
			if (mWidget) {
				if (mWidget->OnLeftClick(GetEye().x+x,GetEye().y+y)) {
					return true;
				}
			}
			if (etk::Widget::OnLeftClick(x, y)) {
				return true;
			}
		}
		return false;
	}

	bool OnRightClick(float x, float y) override {
		if (HitInsideBox(glm::vec2{ x,y })) {
			if (mWidget) {
				if (mWidget->OnRightClick(GetEye().x+x,GetEye().y+y)) {
					return true;
				}
			}
			if (etk::Widget::OnRightClick(x, y)) {
				return true;
			}
		}
		return false;
	}

	void Invalidate() override {
		if (mWidget) {
			SetInternalWidth(mWidget->GetExternalWidth());
			SetInternalHeight(mWidget->GetExternalHeight());
		}
		if (!GetOwner().expired()) GetOwner().lock()->Invalidate();
	}


protected:
	std::shared_ptr<Widget> GetWidget() {
		return mWidget;
	}
private:
	std::shared_ptr<Widget> mWidget;
};
}