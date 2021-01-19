#include "run_on_ui_thread.h"

etk::RunOnUIThread* etk::RunOnUIThread::mSelf{ nullptr };
std::mutex etk::RunOnUIThread::mLock;

bool etk::RunOnUIThread::mInsideExecutioner{ false };
