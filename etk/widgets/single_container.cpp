#include "single_container.h"

void etk::SingleContainer::Init()
{
	if (mWidget) {
		mWidget->Init();
		SetInternalWidth(mWidget->GetExternalWidth());
		SetInternalHeight(mWidget->GetExternalHeight());
	}
	etk::Widget::Init();
}
