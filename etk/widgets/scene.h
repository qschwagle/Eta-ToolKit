#pragma once

#include "multi_container.h"
#include "single_container.h"
#include <unordered_map>
#include <string>
#include <memory>


namespace etk {

class Window;
/**
* Contains the tree and a sets of references to widgets and containers in the tree.
* 
* The identifier in the constructor is used to identifer itself.
* A user should use SetWidget to set the widgets. 
* 
*/
class Scene final : public etk::SingleContainer {
public:
	Scene(std::wstring identifier);
	void Draw() override;
	bool SetWidget(std::wstring identifier, std::wstring target, std::shared_ptr<Widget> widget);
	bool SetWidget(std::wstring identifier, std::wstring target, std::shared_ptr<MultiContainer> widget);
	bool SetWidget(std::wstring identifier, std::wstring target, std::shared_ptr<SingleContainer> widget);
	std::weak_ptr<Widget> GetWidget(std::wstring identifer);
	std::weak_ptr<SingleContainer> GetSingleContainer(std::wstring identifer);
	std::weak_ptr<MultiContainer> GetMultiContainer(std::wstring identifer);
	bool RemoveWidget(std::wstring identifer);

	void SetWindow(std::weak_ptr<Window> w);

	void Update() override {
		SingleContainer::Update();
	}

	std::weak_ptr <etk::renderer::ScreenBox> GetBox();

private:
	std::wstring mSelfIdentifier;
	std::unordered_map<std::wstring, std::weak_ptr<etk::Widget>> mWidgetTable;
	std::unordered_map<std::wstring, std::weak_ptr<etk::MultiContainer>> mMultiContainerTable;
	std::unordered_map<std::wstring, std::weak_ptr<etk::SingleContainer>> mSingleContainerTable;
	/// <summary>
	/// reference
	/// </summary>
	std::weak_ptr<etk::Window> mWindow;
};
}