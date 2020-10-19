#include "GameTestInstance.h"

#include "BaseGameTestFunction.h"
#include "BaseGameTestHelper.h"
#include "GameTestSequence.h"
#include "IGameTestHelperProvider.h"
#include "IGameTestListener.h"

namespace gametest {
	int GameTestInstance::sLevelTick = 0;

	GameTestInstance::GameTestInstance(BaseGameTestFunction& testFunction, IGameTestHelperProvider& helper)
		: mTestFunction(testFunction)
		, mTestHelper(helper.createGameTestHelper(*this)) // NOTE: This might need to move to startExecution so our instance is fully created
		, mTimeoutTicks(testFunction.getMaxTicks()) {
		// TODO: Debug assert mTestHelper
	}

	GameTestInstance::~GameTestInstance() = default;

	void GameTestInstance::addListener(std::shared_ptr<IGameTestListener> listener) {
		mListeners.emplace_back(std::move(listener));
	}

	const std::string& GameTestInstance::getTestName() const {
		return mTestFunction.getTestName();
	}

	int GameTestInstance::getTick() const {
		return mTickCount;
	}

	void GameTestInstance::spawnStructure() {
		// TODO: Implement this
		for (auto&& listener : mListeners) {
			listener->onTestStructureLoaded(*this);
		}
	}

	gametest::GameTestSequence& GameTestInstance::createSequence() {
		auto sequence = std::make_unique<GameTestSequence>(*this);
		GameTestSequence* result = sequence.get();
		mSequences.emplace_back(std::move(sequence));
		return *result;
	}

	void GameTestInstance::startExecution() {
		mStartTick = sLevelTick + 1 + mTestFunction.getSetupTicks();
		//timer.start();
	}

	void GameTestInstance::tick() {
		if (isDone()) {
			return;
		}
		mTickCount = sLevelTick - mStartTick;

		// If we're still setting up
		if (mTickCount < 0) {
			return;
		}
		// If we just started
		else if (mTickCount == 0) {
			startTest();
		}

		if (mTickCount > mTimeoutTicks) {
			// Timed out! Time to end the test.
			if (mSequences.empty()) {
				fail({ GameTestErrorType::Unknown, "Didn't succeed or fail within " + std::to_string(mTestFunction.getMaxTicks()) + " ticks" });
			}
			else {
				for (auto&& sequencePtr : mSequences) {
					sequencePtr->tickAndFailIfNotComplete(mTickCount);
				}

				if (!mError) {
					fail({ GameTestErrorType::Unknown, "No sequences finished" });
				}
			}
		}
		else {
			// Not timed out. We'll end the test only if we have a currentAssert and it is successful
			//sequences.forEach(ticker->ticker.tickAndContinue(tickCount));
			for (auto&& sequencePtr : mSequences) {
				sequencePtr->tickAndContinue(mTickCount);
			}
		}
	}

	void GameTestInstance::startTest() {
		if (mIsStarted) {
			// TODO: Error: Test already started
		}
		mIsStarted = true;
		mTestFunction.run(*mTestHelper);
	}

	bool GameTestInstance::hasSucceeded() const {
		return mIsDone && !mError.has_value();
	}

	bool GameTestInstance::hasFailed() const {
		return mError.has_value();
	}

	bool GameTestInstance::hasStarted() const {
		return mIsStarted;
	}

	bool GameTestInstance::isDone() const {
		return mIsDone;
	}

	bool GameTestInstance::isRequired() const {
		return mTestFunction.isRequired();
	}

	void GameTestInstance::succeed() {
		if (!mError) {
			finish();

			for (auto&& listener : mListeners) {
				listener->onTestPassed(*this);
			}
		}
	}

	void GameTestInstance::fail(GameTestError error) {
		finish();
		mError = std::move(error);

		for (auto&& listener : mListeners) {
			listener->onTestFailed(*this);
		}
	}

	void GameTestInstance::finish() {
		if (!mIsDone) {
			mIsDone = true;
		}
	}

	const std::optional<gametest::GameTestError>& GameTestInstance::getError() const {
		return mError;
	}

} // namespace gametest