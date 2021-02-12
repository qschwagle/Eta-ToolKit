#pragma once

#include "widget.h"

namespace etk {
class SingleContainer : public etk::Widget {
public:
	void Draw() override
	{
		if (mWidget) mWidget->Draw();
	}
	void SetWidget(std::shared_ptr<Widget> widget)
	{
		widget->SetOwner(shared_from_this());
		mWidget = widget;
		mWidget->SetDrawableFactory(GetDrawableFactory());
	}

	void ClearWidget(std::shared_ptr<Widget> widget)
	{
		mWidget = nullptr;
	}

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory) override {
		Widget::SetDrawableFactory(factory);
		if (mWidget) {
			mWidget->SetDrawableFactory(factory);
			Invalidate();
		}
	}

	bool OnScroll(const glm::vec2 point, float xOffset, float yOffset) override {
		if (HitInsideBox(point)) {
			auto shift = GetBox().lock()->GetShift();
			if (!mWidget->OnScroll(shift+point, xOffset, yOffset)) {
				return etk::Widget::OnScroll(point, xOffset, yOffset);
			}
			return true;
		}
	}

	bool OnLeftClick(float x, float y) override {
		if (HitInsideBox(glm::vec2{ x,y })) {
			if (mWidget) {
				auto shift = GetBox().lock()->GetShift();
				if (mWidget->OnLeftClick(shift.x + x, shift.y + y)) {
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
				auto box = GetBox().lock()->GetDimensions(); 
				if (mWidget->OnRightClick(box.x+x, box.y+y)) {
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

	std::shared_ptr<Widget> Clone() override {
		auto out = std::dynamic_pointer_cast<SingleContainer>(Widget::Clone());
		if (mWidget) out->mWidget = mWidget->Clone();
		out->mWidget->SetOwner(out);
		return out;
	}

	void SetPosition(glm::vec2 pos) override {
		Widget::SetPosition(pos);
		if (mWidget) mWidget->SetPosition(pos);
	}



protected:
	std::shared_ptr<Widget> GetWidget() {
		return mWidget;
	}
private:
	std::shared_ptr<Widget> mWidget;
};
}