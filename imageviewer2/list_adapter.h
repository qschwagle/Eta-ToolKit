#pragma once

#include <etk/widgets/list_view.h>

#include <string>
#include <memory>
#include <vector>

/// <summary>
/// We are adapting a vector<wstring> to be used with ListView
/// </summary>
class ListAdapter : public etk::ListView<std::wstring>::ListModelDataPointer {
public:

	ListAdapter(int pos, std::weak_ptr<std::vector<std::wstring>> list) {
		mPos = pos;
		mFileList = list;
	}

	bool IsBegin() const override {
		return mPos < 0;
	}

	bool IsEnd() const override {
		return mPos >= mFileList.lock()->size();
	}

	ListModelDataPointer* FetchFirst() override {
		return new ListAdapter(0, mFileList);
	}

	ListModelDataPointer* FetchLast() override {
		return new ListAdapter(mFileList.lock()->size()-1, mFileList);
	}

	etk::ListView<std::wstring>::ListModelDataPointer* Fetch(int i) override {
		return new ListAdapter(mPos + i, mFileList);
	}

	void Map(std::wstring* data, std::shared_ptr<etk::Scene> scene) override {
		auto title = std::dynamic_pointer_cast<etk::Label>(scene->GetWidget(L"TITLE").lock());
		title->SetText(*data);
	}

private:
	int mPos;
	std::weak_ptr<std::vector<std::wstring>> mFileList;
};