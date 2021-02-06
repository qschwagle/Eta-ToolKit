#pragma once

namespace etk {
namespace renderer {
class UIAnimation {
public:
	virtual bool Run(long msTimeSinceLastRender) {}
};
}
}