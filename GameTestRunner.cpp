#include "GameTestRunner.h"

#include "BaseGameTestFunction.h"
#include "ConsoleGameTestListener.h"
#include "GameTestBatchRunner.h"
#include "GameTestInstance.h"
#include "GameTestTicker.h"

namespace gametest {

	void GameTestRunner::runTest(std::shared_ptr<GameTestInstance> test, GameTestTicker& ticker) {
		test->startExecution();
		ticker.add(test);
		test->addListener(std::make_shared<ConsoleGameTestListener>());
		test->spawnStructure();
	}

	std::vector<GameTestBatch> GameTestRunner::groupTestsIntoBatches(const std::vector<std::shared_ptr<BaseGameTestFunction>>& testFunctions) {
		std::unordered_map<std::string, std::vector<std::shared_ptr<BaseGameTestFunction>>> testFunctionsPerBatch;

		// Make a map with TestFunctions grouped by batch name.
		for (auto&& testFunction : testFunctions) {
			auto& batchName = testFunction->getBatchName();
			testFunctionsPerBatch[batchName].emplace_back(testFunction);
		}

		std::vector<GameTestBatch> result;
		result.reserve(testFunctionsPerBatch.size());
		for (auto&& batchItr : testFunctionsPerBatch) {
			result.emplace_back(GameTestBatch(batchItr.first, std::move(batchItr.second)));
		}

		return result;
	}

	std::unique_ptr<GameTestBatchRunner> GameTestRunner::runTestBatches(IGameTestHelperProvider& helperProvider, const std::vector<GameTestBatch>& batches, GameTestTicker& testTicker, int testsPerRow) {
		auto runner = std::make_unique<GameTestBatchRunner>(helperProvider, batches, testTicker, testsPerRow);
		runner->start();
		return runner;
	}

} // namespace gametest
