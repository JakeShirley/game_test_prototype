#include "GameTestSequence.h"

#include "BaseGameTestAction.h"
#include "GameTestInstance.h"
#include "NativeFunctionGameTestAction.h"

#include <sstream>

namespace gametest
{
  
	GameTestSequence::GameTestSequence(GameTestInstance &testInstance) 
		: mTestInstance(testInstance)
		, mLastTick(testInstance.getTick()) {
	}

	GameTestSequence::~GameTestSequence() = default;

	GameTestSequence & GameTestSequence::thenWait(int expectedDelay, GameTestActionCallback action) {
		mActions.emplace_back(std::make_unique<NativeFunctionGameTestAction>(expectedDelay, std::move(action)));
		return *this;
	}

	GameTestSequence & GameTestSequence::thenWait(GameTestActionCallback action) {
		mActions.emplace_back(std::make_unique<NativeFunctionGameTestAction>(std::move(action)));
		return *this;
	}

	void GameTestSequence::thenSucceed() {
		mActions.emplace_back(std::make_unique<NativeFunctionGameTestAction>([&]() {
			mTestInstance.succeed();
			return std::nullopt;
		}));
	}

	void GameTestSequence::tickAndFailIfNotComplete(int currentTick) {
		auto result = tick(currentTick);
		if (result) {
			mTestInstance.fail(result.value());
		}
	}

	void GameTestSequence::tickAndContinue(int currentTick) {
		tick(currentTick);
	}

	std::optional<gametest::GameTestError> GameTestSequence::tick(int currentTick) {
		for (auto actionItr = mActions.begin(); actionItr != mActions.end();)
		{
			BaseGameTestAction &action = *actionItr->get();
			auto actionResult = action.run();

			// Return now if our action error'd
			if (actionResult)
			{
				return actionResult;
			}

			const int delay = currentTick - mLastTick;
			const int previousTick = mLastTick;
			mLastTick = currentTick;

			if (action.getExpectedDelay() && action.getExpectedDelay() != delay)
			{
				std::stringstream ss;
				ss << "Succeeded in invalid tick: expected " << (previousTick + action.getExpectedDelay().value()) << ", but current tick is " << currentTick;
				mTestInstance.fail({ GameTestErrorType::Unknown, ss.str() });
				break;
			}

			actionItr = mActions.erase(actionItr);
		}

		return std::nullopt;
	}

} // namespace gametest
