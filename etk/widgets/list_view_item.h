#pragma once

#include "scene.h"


/// <summary>
/// Represents a Widget within a List View.
/// </summary>
/// <remark>
/// Should not be instantiated by any class other than ListView
/// </remark>
namespace etk {
class ListViewItem : public Widget {
public:
	ListViewItem() = default;
	ListViewItem(const ListViewItem&) = delete;
	ListViewItem& operator=(const ListViewItem&) = delete;

	void SetScene(std::shared_ptr<Scene> scene) {
		mScene = scene; 
		scene->SetOwner(shared_from_this());
		if(!GetDrawableFactory().expired()) mScene->SetDrawableFactory(GetDrawableFactory());
		//Invalidate();
	} 
	void Draw() override {
		mScene->Draw();
	}

	void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> fact) override {
		Widget::SetDrawableFactory(fact);
		if(mScene) mScene->SetDrawableFactory(fact);
		Invalidate();
	}

	bool OnScroll(const glm::vec2 point, float xOffset, float yOffset) override {
		if (HitInsideBox(point)) {
			auto shift = GetBox().lock()->GetShift();
			if (!mScene->OnScroll(shift + point, xOffset, yOffset)) {
				return etk::Widget::OnScroll(point, xOffset, yOffset);
			}
			return true;
		}
	}

	bool OnLeftClick(float x, float y) override {
		if (HitInsideBox(glm::vec2{ x,y })) {
			if (mScene) {
				auto shift = GetBox().lock()->GetShift();
				if (mScene->OnLeftClick(shift.x + x, shift.y + y)) {
					return true;
				}
			}
			if (etk::Widget::OnLeftClick(x, y)) {
				return true;
			}
		}
		return false;
	}

	bool OnRightClick(float x, float y) override {
		if (HitInsideBox(glm::vec2{ x,y })) {
			if (mScene) {
				auto box = GetBox().lock()->GetDimensions();
				if (mScene->OnRightClick(box.x + x, box.y + y)) {
					return true;
				}
			}
			if (etk::Widget::OnRightClick(x, y)) {
				return true;
			}
		}
		return false;
	}

	void Update() override;

	void SetPosition(glm::vec2 pos) override {
		Widget::SetPosition(pos);
		if (mScene) mScene->SetPosition(pos);
	}


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