#pragma once

namespace etk {
namespace renderer {
class UIAction {
public:
	virtual bool Run(void) { return false;  }
private:
};
}
}