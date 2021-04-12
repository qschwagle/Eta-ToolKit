#include "list_view_item.h"

void etk::ListViewItem::Update()
{
	if (mScene) {
		mScene->Update();
		SetInternalWidth(mScene->GetExternalWidth());
		SetInternalHeight(mScene->GetExternalHeight());
	}
}