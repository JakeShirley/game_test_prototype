#pragma once

#include "GameTestActionCallback.h"

#include <functional>

namespace gametest {
	class GameTestInstance;

	class BaseGameTestHelper {
	public:
		BaseGameTestHelper(GameTestInstance& testInstance);
		virtual ~BaseGameTestHelper() = default;

		void succeed();
		void succeedIf(GameTestActionCallback fn);

	private:
		GameTestInstance& mTestInstance;
		const int mTickCount = 0;
		const int mStartTick = 0;
		const int mTimeoutTicks = 0;
		bool mIsDone = false;
	};
} // namespace gametest