#pragma once

#include "multi_container.h"

namespace etk {
class LinearLayout : public MultiContainer {
public:
	LinearLayout() = default;
	LinearLayout(const LinearLayout&) = delete;
	LinearLayout& operator=(const LinearLayout&) = delete;
	

	void AddWidget(std::shared_ptr<Widget> widget) override;
	
	void SetPosition(const glm::vec2 pos) override;

	void Init() override;

protected:

	void UpdateChildrenPositions() override;

private:
	std::array<float, 2> mNextLocation{ 0.0f,0.0f };

};
}