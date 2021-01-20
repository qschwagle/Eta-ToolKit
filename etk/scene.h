#pragma once

#include "widget.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace etk {
class Scene : public etk::Widget {
public:
	void Draw() override;

private:
	std::unordered_map <std::wstring, std::weak_ptr<etk::Widget>> mWidgetTable;
};
}