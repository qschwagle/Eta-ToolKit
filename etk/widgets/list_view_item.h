#pragma once

#include "scene.h"

/// <summary>
/// Represents a Widget within a List View.
/// </summary>
/// <remark>
/// Should not be instantiated by any class other than ListView
/// </remark>
namespace etk {
class ListViewItem {
public:
	ListViewItem() = default;
	ListViewItem(const ListViewItem&) = delete;
	ListViewItem& operator=(const ListViewItem&) = delete;

private:

	/// <summary>
	/// unique scene for this ListViewItem
	/// </summary>
	std::shared_ptr<Scene> mScene;

	/// <summary>
	/// pointer to the data represented in the scene
	/// </summary>
};
}