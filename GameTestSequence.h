#pragma once

#include "GameTestActionCallback.h"
#include "GameTestError.h"

#include <memory>

namespace gametest {
	class BaseGameTestAction;
	class GameTestInstance;

	class GameTestSequence {
	public:
		GameTestSequence(GameTestInstance& testInstance);
		~GameTestSequence();

		GameTestSequence& thenWait(GameTestActionCallback action);
		GameTestSequence& thenWait(int expectedDelay, GameTestActionCallback action);

		void thenSucceed();

		void tickAndFailIfNotComplete(int currentTick);
		void tickAndContinue(int currentTick);
		std::optional<GameTestError> tick(int currentTick);

	private:
		int mLastTick = 0;

		GameTestInstance& mTestInstance;
		std::vector<std::unique_ptr<BaseGameTestAction>> mActions;
	};
} // namespace gametest
