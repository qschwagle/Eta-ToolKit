#pragma once

#include "widget.h"
#include "scene.h"
#include "scene_builder.h"
#include "list_view_item.h"

#include <memory>
#include <map>

namespace etk {

template<typename T>
class ListView : public Widget {
public:
	ListView() = default;
	ListView(const ListView&) = delete;
	ListView& operator=(const ListView&) = delete;

	virtual ~ListView() {
		if (mModel) delete mModel;
	}

	/// <summary>
	/// A Bidirectional iterator style pointer.
	/// There should be a sentinel on either end which does not contain data.
	/// Do to the nature of the iterator, Begin() is any point which is before the start of the data and end is any point at the end of the data
	/// All operations done outside of map does not depend on ui, Map requires running on UI Context Thread
	/// </summary>
	/// <typeparam name="T"></typeparam>
	class ListModelDataPointer {
	public:
		/// <summary>
		/// Should retrieve a a complete data. Fetches Data from a relative point.
		/// should be bidirectional
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		virtual ListModelDataPointer* Fetch(int i) { return nullptr; }
	
		/// <summary>
		/// map data to scene
		/// </summary>
		/// <param name="data">data</param>
		/// <param name="scene"></param>
		virtual void Map(T* data, std::shared_ptr<Scene> scene) {}
	
		virtual bool IsBegin() const { return false;  }
		
		virtual bool IsEnd() const { return false;  }
	
		virtual ListModelDataPointer* FetchFirst() { return nullptr; }
	
		virtual ListModelDataPointer* FetchLast() { return nullptr; }

		virtual T* GetData() { return nullptr; }
	
		virtual void Notify() {
			mView.lock()->Update();
		}
	
		virtual void SetListView(std::weak_ptr<ListView<T>> view) {
			mView = view;
		}
	
	private:
		/// <summary>
		/// reference to the view which uses this pointer
		/// </summary>
		std::weak_ptr<ListView<T>> mView;
	};

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> fact) override {
		if (!fact.expired()) {
			Widget::SetDrawableFactory(fact);

			// we should initialize a set of items if we have a ListModelDataPointer
			if (mModel) {
				Update();
			}
			// we should setup factories if they don't already exist
			for (auto i : mItems) {
				i.second->SetDrawableFactory(fact);
			}
		}
	}

	/// <summary>
	/// ListView takes ownership of the pointer and will delete it when the ListView is freed.
	/// It will also delete it if supplied with a second model
	/// </summary>
	/// <param name="m"></param>
	virtual void SetModel(ListModelDataPointer* m) {
		if (mModel) delete mModel;
		mModel = m;
		mModel->SetListView(std::dynamic_pointer_cast<ListView<T>>(shared_from_this()));
	}

	virtual void SetSceneBuilder(std::shared_ptr<SceneBuilder> builder) {
		mBuilder = builder;
	}

	virtual void Update() {
		auto i = mModel->FetchFirst();
		mBaseIndex = 0;
		long index = mBaseIndex;
		while (!i->IsEnd()) {
			auto item = std::make_shared<ListViewItem>();
			item->SetDrawableFactory(GetDrawableFactory());
			auto scene = mBuilder->CreateScene();
			i->Map(i->GetData(), scene);
			item->SetScene(scene);
			mItems.emplace(index, item);
			++index;
			i = i->Fetch(1);
		}
	}

	virtual void Draw() override {
		for (auto i : mItems) {
			i.second->Draw();
		}
	}

private:
	/// <summary>
	/// Model associated with the ListView
	/// </summary>
	ListModelDataPointer* mModel{ nullptr };

	std::shared_ptr<SceneBuilder> mBuilder;

	long mBaseIndex{ 0 };
	std::map<long, std::shared_ptr<etk::ListViewItem>> mItems;
};
}