#include "scene.h"
#include <utility>

etk::Scene::Scene(std::wstring identifier) : mSelfIdentifier{identifier}
{
}

void etk::Scene::Draw(const glm::vec2& eye)
{
	SingleContainer::Draw(eye + GetEye());
}

bool etk::Scene::SetWidget(std::wstring identifier, std::wstring target, std::shared_ptr<etk::Widget> widget)
{
	if (mSelfIdentifier == target) {
		etk::SingleContainer::SetWidget(widget);
		mWidgetTable.insert_or_assign(identifier, widget);
		return true;
	}
	auto si = mSingleContainerTable.find(target);
	auto mi = mMultiContainerTable.find(target);
	if (mi != mMultiContainerTable.end()) {
		auto shared = mi->second.lock();
		shared->AddWidget(widget);
		mWidgetTable.insert_or_assign(identifier, widget);
		return true;
	}
	else if (si != mSingleContainerTable.end()) {
		auto shared = si->second.lock();
		shared->SetWidget(widget);
		mWidgetTable.insert_or_assign(identifier, widget);
		return true;
	}
	else {
		return false;
	}
}


bool etk::Scene::SetWidget(std::wstring identifier, std::wstring target, std::shared_ptr<etk::SingleContainer> widget)
{
	if (mSelfIdentifier == target) {
		etk::SingleContainer::SetWidget(widget);
		mSingleContainerTable.insert_or_assign(identifier, widget);
		return true;
	}
	auto si = mSingleContainerTable.find(target);
	auto mi = mMultiContainerTable.find(target);
	if (mi != mMultiContainerTable.end()) {
		auto shared = mi->second.lock();
		shared->AddWidget(widget);
		mSingleContainerTable.insert_or_assign(identifier, widget);
		return true;
	}
	else if (si != mSingleContainerTable.end()) {
		auto shared = si->second.lock();
		shared->SetWidget(widget);
		mSingleContainerTable.insert_or_assign(identifier, widget);
		return true;
	}
	else {
		return false;
	}
}

bool etk::Scene::SetWidget(std::wstring identifier, std::wstring target, std::shared_ptr<etk::MultiContainer> widget)
{
	if (mSelfIdentifier == target) {
		etk::SingleContainer::SetWidget(widget);
		mMultiContainerTable.insert_or_assign(identifier, widget);
		return true;
	}
	auto si = mSingleContainerTable.find(target);
	auto mi = mMultiContainerTable.find(target);
	if (mi != mMultiContainerTable.end()) {
		auto shared = mi->second.lock();
		shared->AddWidget(widget);
		mMultiContainerTable.insert_or_assign(identifier, widget);
		return true;
	}
	else if (si != mSingleContainerTable.end()) {
		auto shared = si->second.lock();
		shared->SetWidget(widget);
		mMultiContainerTable.insert_or_assign(identifier, widget);
		return true;
	}
	else {
		return false;
	}
}

std::weak_ptr<etk::Widget> etk::Scene::GetWidget(std::wstring identifer)
{
	{
		auto wi = mWidgetTable.find(identifer);
		if (wi != mWidgetTable.end()) {
			return wi->second;
		}
	}

	{
		auto mi = mMultiContainerTable.find(identifer);
		if (mi != mMultiContainerTable.end()) {
			return mi->second;
		}
	}
	{
		auto si = mSingleContainerTable.find(identifer);
		if (si != mSingleContainerTable.end()) {
			return si->second;
		}
	}
	return std::weak_ptr<etk::Widget>();
}

std::weak_ptr<etk::SingleContainer> etk::Scene::GetSingleContainer(std::wstring identifer)
{
	{
		auto si = mSingleContainerTable.find(identifer);
		if (si != mSingleContainerTable.end()) {
			return si->second;
		}
	}
	return std::weak_ptr<etk::SingleContainer>();
}

std::weak_ptr<etk::MultiContainer> etk::Scene::GetMultiContainer(std::wstring identifer)
{
	{
		auto mi = mMultiContainerTable.find(identifer);
		if (mi != mMultiContainerTable.end()) {
			return mi->second;
		}
	}
	return std::weak_ptr<etk::MultiContainer>();
}

bool etk::Scene::RemoveWidget(std::wstring identifer)
{
	{
		auto wi = mWidgetTable.find(identifer);
		if (wi != mWidgetTable.end()) {
			mWidgetTable.erase(wi);
			return true;
		}
	}

	{
		auto mi = mMultiContainerTable.find(identifer);
		if (mi != mMultiContainerTable.end()) {
			mMultiContainerTable.erase(mi);
			return true;
		}
	}
	{
		auto si = mSingleContainerTable.find(identifer);
		if (si != mSingleContainerTable.end()) {
			mSingleContainerTable.erase(si);
			return true;
		}
	}
	return false;
}
