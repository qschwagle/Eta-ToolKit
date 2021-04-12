#include "linear_container.h"

void etk::LinearContainer::AddWidget(std::shared_ptr<Widget> widget)
{
	etk::MultiContainer::AddWidget(widget);
	widget->SetPosition(glm::vec2(mNextLocation[0], mNextLocation[1]));
	mNextLocation[1] += widget->GetExternalHeight();
}

void etk::LinearContainer::SetPosition(const glm::vec2 pos)
{
	etk::Widget::SetPosition(pos);
	mNextLocation = { pos.x, pos.y };
	UpdateChildrenPositions();
}

void etk::LinearContainer::UpdateChildrenPositions()
{
	switch (mDirection) {
	case Direction::VERTICAL: 
	{
		mNextLocation = { GetPosition().x, GetPosition().y };
		float greatestWidth = 0.0f;
		for (auto& i : GetWidgetList()) {
			i->SetPosition(glm::vec2(mNextLocation[0], mNextLocation[1]));
			i->Update();
			mNextLocation[1] += i->GetExternalHeight();
			greatestWidth = i->GetExternalWidth() > greatestWidth ? i->GetExternalWidth() : greatestWidth;
		}
		SetInternalWidth(greatestWidth);
		if (GetWidgetList().size() > 0) {
			SetInternalHeight(mNextLocation[1] - GetPosition().y);
		}
		break;
	}

	case Direction::HORIZONTAL:
	{
		mNextLocation = { GetPosition().x, GetPosition().y };
		float greatestHeight = 0.0f;
		for (auto& i : GetWidgetList()) {
			i->SetPosition(glm::vec2(mNextLocation[0], mNextLocation[1]));
			i->Update();
			mNextLocation[0] += i->GetExternalWidth();
			greatestHeight = i->GetExternalHeight() > greatestHeight ? i->GetExternalHeight() : greatestHeight;
		}
		SetInternalHeight(greatestHeight);
		if (GetWidgetList().size() > 0) {
			SetInternalWidth(mNextLocation[0] + GetPosition().x + GetWidgetList().back()->GetExternalWidth());
		}
		break;
	}
	}
}

void etk::LinearContainer::Update()
{
	UpdateChildrenPositions();
}
