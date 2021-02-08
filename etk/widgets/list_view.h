#pragma once

#include "widget.h"
#include "scene.h"
#include <memory>

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
	
		virtual void Notify() {
			mView->Update();
		}
	
		virtual void SetListView(ListView<T>* view) {
			mView = view;
		}
	
		virtual void SetScene() {
	
		}
	private:
		ListView<T>* mView;
	};

	/// <summary>
	/// ListView takes ownership of the pointer and will delete it when the ListView is freed.
	/// It will also delete it if supplied with a second model
	/// </summary>
	/// <param name="m"></param>
	virtual void SetModel(ListModelDataPointer* m) {
		if (mModel) delete mModel;
		mModel = m;
		mModel->SetListView(this);
	}



	virtual void Update() {}

private:
	/// <summary>
	/// Model associated with the ListView
	/// </summary>
	ListModelDataPointer* mModel{ nullptr };
};
}