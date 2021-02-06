#pragma once

#include <functional>
#include <mutex>
#include <vector>
#include <array>
#include <iterator>
#include <memory>

#include "ui_action.h"
#include "ui_animation.h"
#include "ui_action_func.h"

namespace etk {
namespace renderer {
class UIThreadScheduler {
public:
	UIThreadScheduler()=default;

	void Schedule(std::unique_ptr<UIAnimation> action) {
		mLock.lock();
		mAnimationScheduleLists[mNext].push_back(std::move(action));
		mLock.unlock();
	}

	void Schedule(std::unique_ptr<UIAction> action) {
		mLock.lock();
		mUIScheduleLists[mNext].push_back(std::move(action));
		mLock.unlock();
	}

	void Schedule(std::function<bool()> func) {
		mLock.lock();
		mUIScheduleLists[mNext].push_back(std::make_unique<etk::renderer::UIActionFunc>(func));
		mLock.unlock();
	}

	void Execute() {
		mLock.lock();
		auto end = std::make_move_iterator(mUIScheduleLists[mNext].end());
		for (auto i = std::make_move_iterator(mUIScheduleLists[mNext].begin()); i != end; ++i) {
			if ((*i)->Run()) {
				mUIScheduleLists[!mNext].push_back(std::move(*i));
			}
		}
		mUIScheduleLists[mNext].clear();
		auto end2 = std::make_move_iterator(mAnimationScheduleLists[mNext].end());
		for (auto i = std::make_move_iterator(mAnimationScheduleLists[mNext].begin()); i != end2; ++i) {
			if ((*i)->Run(0)) {
				mAnimationScheduleLists[!mNext].push_back(std::move(*i));
			}
		}
		mAnimationScheduleLists[mNext].clear();
		mNext = !mNext;
		mLock.unlock();
	}

	bool AnimationQueued() const
	{
		return mAnimationScheduleLists[mNext].size() != 0;
	}

	bool UIActionQueued() const
	{
		return mUIScheduleLists[mNext].size() != 0;
	}

private:
	std::recursive_mutex mLock;
	int  mNext{ 0 };
	std::array<std::vector<std::unique_ptr<UIAction>>, 2>  mUIScheduleLists;
	std::array<std::vector<std::unique_ptr<UIAnimation>>, 2> mAnimationScheduleLists;
};
}
}