#include "linear_layout.h"

void etk::LinearLayout::AddWidget(std::shared_ptr<Widget> widget)
{
	etk::MultiContainer::AddWidget(widget);
	widget->SetPosition(glm::vec2(mNextLocation[0], mNextLocation[1]));
	mNextLocation[1] += widget->GetExternalHeight();
}

void etk::LinearLayout::SetPosition(const glm::vec2 pos)
{
	etk::Widget::SetPosition(pos);
	mNextLocation = { pos.x, pos.y };
	UpdateChildrenPositions();
}

void etk::LinearLayout::Invalidate()
{
	UpdateChildrenPositions();
	if (!GetOwner().expired()) GetOwner().lock()->Invalidate();
}

void etk::LinearLayout::UpdateChildrenPositions()
{
	mNextLocation = { GetPosition().x, GetPosition().y };
	float greatestWidth = 0.0f;
	for (auto& i : GetWidgetList()) {
		i->SetPosition(glm::vec2(mNextLocation[0], mNextLocation[1]));
		mNextLocation[1] += i->GetExternalHeight();
		greatestWidth = i->GetExternalWidth() > greatestWidth ? i->GetExternalWidth() : greatestWidth;
	}
	SetInternalWidth(greatestWidth);
	if (GetWidgetList().size() > 0) {
		SetInternalHeight(mNextLocation[1] - GetPosition().y + GetWidgetList().back()->GetExternalHeight());
	}
}
