
#include <memory>

#include "GameTestInstance.h"
#include "NativeGameTestFunction.h"
#include "BaseGameTestHelper.h"
#include "ConsoleGameTestListener.h"
#include "GameTestBatchRunner.h"
#include "GameTestRunner.h"
#include "GameTestTicker.h"
#include "IGameTestHelperProvider.h"

class DebugGameTestHelperProvider : public gametest::IGameTestHelperProvider {
public:
	virtual std::unique_ptr<gametest::BaseGameTestHelper> createGameTestHelper(gametest::GameTestInstance &testInstance) {
		return std::make_unique<gametest::BaseGameTestHelper>(testInstance);
	}
};

std::shared_ptr<gametest::BaseGameTestFunction> generateFunction(const std::string& batch, const std::string& fnName, bool pass) {
	return std::make_shared<gametest::NativeGameTestFunction>(batch, fnName, batch + "_" + fnName + "_structure", 100, 0, true, [pass](gametest::BaseGameTestHelper& helper) {
		helper.succeedIf([pass]() -> std::optional<gametest::GameTestError> {
			if (pass) {
				return std::nullopt;
			}
			else {
				return gametest::GameTestError{ gametest::GameTestErrorType::Unknown, "Failed because fuck you that's why" };
			}
		});
	});
}

int main() {
	std::vector<std::shared_ptr<gametest::BaseGameTestFunction>> tests;
	for (int i = 0; i < 10; ++i) {
		tests.emplace_back(generateFunction("batch" + std::to_string(i / 3), std::to_string(i), i % 2 == 0));
	}

	DebugGameTestHelperProvider testHelper;
	gametest::GameTestTicker testTicker;

	auto testBatches = gametest::GameTestRunner::groupTestsIntoBatches(tests);
	auto testBatchRunner = gametest::GameTestRunner::runTestBatches(testHelper, testBatches, testTicker, 5);

	while (!testTicker.empty()) {
		testTicker.tick();
		gametest::GameTestInstance::sLevelTick++;
	}

	return 0;
}