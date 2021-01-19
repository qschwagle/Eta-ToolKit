#include "RunOnUIThread.h"

etk::RunOnUIThread* etk::RunOnUIThread::mSelf{ nullptr };
std::mutex etk::RunOnUIThread::mLock;

bool etk::RunOnUIThread::mInsideExecutioner{ false };
