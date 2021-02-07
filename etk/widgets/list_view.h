#pragma once

#include "widget.h"
#include "scene.h"
#include <memory>

namespace etk {
class ListView;

/// <summary>
/// A Bidirectional iterator style pointer.
/// There should be a sentinel on either end which does not contain data.
/// Do to the nature of the iterator, Begin() is any point which is before the start of the data and end is any point at the end of the data
/// All operations done outside of map does not depend on ui, Map requires running on UI Context Thread
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class ListModelDataPointer {
	/// <summary>
	/// Should retrieve a a complete data. Fetches Data from a relative point.
	/// should be bidirectional
	/// </summary>
	/// <param name="i"></param>
	/// <returns></returns>
	ListModelDataPointer* Fetch(int i) { return nullptr; }

	/// <summary>
	/// map data to scene
	/// </summary>
	/// <param name="data">data</param>
	/// <param name="scene"></param>
	void Map(T* data, std::shared_ptr<Scene> scene) {}

	bool IsBegin() const { return false;  }
	
	bool IsEnd() const { return false;  }

	ListModelDataPointer* FetchFirst() { return nullptr; }

	ListModelDataPointer* FetchLast() { return nullptr; }
};

class ListView : public Widget, std::enable_shared_from_this {
public:
	ListView() = default;
	ListView(const List&) = delete;
	ListView& operator=(const ListView&) = delete;

	virtual ~ListView() {}

	void SetModel(std::shared_ptr<T> m) {
		mModel = m;
	}

	void SetScene() 
private:
	/// <summary>
	/// Model associated with the ListView
	/// </summary>
	std::shared_ptr<ListModel> mModel;
};
}