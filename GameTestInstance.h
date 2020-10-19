#pragma once

#include "GameTestError.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace gametest {
	class BaseGameTestFunction;
	class BaseGameTestHelper;
	class GameTestSequence;
	class IGameTestHelperProvider;
	class IGameTestListener;

	class GameTestInstance {
	public:
		// DEBUG HACK
		static int sLevelTick;

		GameTestInstance(BaseGameTestFunction& testFunction, IGameTestHelperProvider& helper);
		~GameTestInstance();

		void addListener(std::shared_ptr<IGameTestListener> listener);

		const std::string& getTestName() const;
		int getTick() const;

		void spawnStructure();

		GameTestSequence& createSequence();

		/**
		 * Ends the test on timeout, or if succeedWhenThisAssertPasses passes.
		 */
		void tick();

		void startExecution();
		void startTest();

		bool hasSucceeded() const;
		bool hasFailed() const;
		bool hasStarted() const;
		bool isDone() const;
		bool isRequired() const;

		void succeed();
		void fail(GameTestError error);
		void finish();

		const std::optional<GameTestError>& getError() const;

	private:
		std::unique_ptr<BaseGameTestHelper> mTestHelper;
		std::vector<std::shared_ptr<IGameTestListener>> mListeners;
		std::vector<std::unique_ptr<GameTestSequence>> mSequences;

		std::optional<GameTestError> mError;

		BaseGameTestFunction& mTestFunction;
		int mTickCount = 0;
		int mStartTick = 0;
		const int mTimeoutTicks = 0;
		const int mSetupTicks = 0;
		bool mIsDone = false;
		bool mIsStarted = false;
	};
} // namespace gametest