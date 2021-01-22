#pragma once

#include <functional>
#include <mutex>
#include <vector>
#include <array>

namespace etk {
namespace renderer {
class UIThreadScheduler {
public:
	UIThreadScheduler()=default;

	void Schedule(std::function<bool()> func) {
		mLock.lock();
		mScheduleLists[mNext].push_back(func);
		mLock.unlock();
	}

	void Execute() {
		mLock.lock();
		for (const auto& i: mScheduleLists[mNext]) {
			if (i()) {
				mScheduleLists[!mNext].push_back(i);
			}
		}
		mScheduleLists[mNext].clear();
		mNext = !mNext;
		mLock.unlock();
	}

private:
	std::recursive_mutex mLock;
	int  mNext{ 0 };
	std::array <std::vector<std::function<bool()>>, 2>  mScheduleLists;
};
}
}