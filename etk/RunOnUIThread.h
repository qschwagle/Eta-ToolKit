#pragma once

#include <mutex>
#include <vector>
#include <functional>

namespace etk {
class RunOnUIThread {
public:
	RunOnUIThread(const RunOnUIThread&) = delete;
	RunOnUIThread& operator=(const RunOnUIThread&) = delete;

	static RunOnUIThread* GetInstance() {
		if(!mInsideExecutioner) mLock.lock();
		if (!mSelf) mSelf = new RunOnUIThread();
		if(!mInsideExecutioner) mLock.unlock();
		return mSelf;
	}

	void ScheduleFunc(std::function<bool()> func) {
		if(!mInsideExecutioner) mLock.lock();
		mScheduled.push_back(func);
		if(!mInsideExecutioner) mLock.unlock();
	}

	void Execute(void) {
		mLock.lock();
		mInsideExecutioner = true;
		for (auto i : mScheduled) {
			if (i()) {
				mNext.push_back(i);
			}
		}
		mScheduled = mNext;
		mNext.clear();
		mInsideExecutioner = false;
		mLock.unlock();
	}
private:
	RunOnUIThread() {}
	static RunOnUIThread* mSelf;
	static std::mutex mLock;
	static bool mInsideExecutioner;
	std::vector<std::function<bool()>> mScheduled;
	std::vector<std::function<bool()>> mNext;
};
}