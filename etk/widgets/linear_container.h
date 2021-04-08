#pragma once

#include "multi_container.h"

namespace etk {
class LinearContainer : public MultiContainer {
public:
	LinearContainer() = default;
	LinearContainer(const LinearContainer&) = delete;
	LinearContainer& operator=(const LinearContainer&) = delete;
	

	void AddWidget(std::shared_ptr<Widget> widget) override;
	
	void SetPosition(const glm::vec2 pos) override;

	void Update() override;

	enum class Direction {
		HORIZONTAL = 0,
		VERTICAL = 1
	};


	void SetDirection(Direction d) {
		mDirection = d;
	}

	
protected:

	void UpdateChildrenPositions() override;

private:
	std::array<float, 2> mNextLocation{ 0.0f,0.0f };
	Direction mDirection = Direction::VERTICAL;

};
}