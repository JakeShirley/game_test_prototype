#pragma once

#include "GameTestActionCallback.h"

#include <functional>

namespace gametest {
	class GameTestInstance;

	///
	// A class that is the "model" for GameTestInstances and provides access to world data
	///
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