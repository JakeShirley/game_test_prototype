#pragma once

#include "GameTestBatch.h"

#include <string>

namespace gametest {
	class GameTestBatchRunner;
	class GameTestInstance;
	class GameTestTicker;
	class IGameTestHelperProvider;

	class GameTestRunner {
	public:
		static void runTest(std::shared_ptr<GameTestInstance> test, GameTestTicker& ticker);

		static std::vector<GameTestBatch> groupTestsIntoBatches(const std::vector<std::shared_ptr<BaseGameTestFunction>>& testFunctions);

		static std::unique_ptr<GameTestBatchRunner> runTestBatches(IGameTestHelperProvider& helperProvider, const std::vector<GameTestBatch>& batches, GameTestTicker& testTicker, int testsPerRow);
	};
} // namespace gametest
