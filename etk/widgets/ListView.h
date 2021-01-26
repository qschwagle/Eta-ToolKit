#pragma once

#include "widget.h"

#include <memory>

namespace etk {

class ListView;

template<typename T>
class ListModel {
public:
	void UpdateObserver() {
		if (!mView.expired()) mView.lock()->Update();
	}
	/* Should only be called ListView */
	void SetViewObserver(std::weak_ptr<ListView> ob) {
		mView = ob;
	}

	void etk::Scene CreateViewItem(T& dataItem) {

	}
private:
	std::weak_ptr<ListView> mView;
};
/**
* Predefined ViewModel
*
* 
*/
class ListView : public Widget, std::enable_shared_from_this {
public:
	ListView() = default;
	ListView(const List&) = delete;
	ListView& operator=(const ListView&) = delete;

	virtual ~ListView() {}

	void Update() {

	}

	void SetModel(std::shared_ptr<T> m) {
		mModel = m;
	}

	void SetScene() 
private:

	std::shared_ptr<ListModel> mModel;


};
}