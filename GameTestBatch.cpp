#include "GameTestBatch.h"

namespace gametest
{
	const std::string GameTestBatch::sDefaultBatchName = "defaultBatch";
	
	GameTestBatch::GameTestBatch(std::string name, std::vector<std::shared_ptr<BaseGameTestFunction>> testFunctions, BeforeBatchFunction beforeBatchFunction /*= nullptr*/) 
		: mName(std::move(name))
		, mTestFunctions(std::move(testFunctions))
		, mBeforeBatchFunction(std::move(beforeBatchFunction)) 
	{
		if (mTestFunctions.empty()) {
			// TODO: Error "A GameTestBatch must include at least one TestFunction!"
		}
	}

	const std::string& GameTestBatch::getName() {
		return mName;
	}

	const std::vector<std::shared_ptr<gametest::BaseGameTestFunction>>& GameTestBatch::getTestFunctions() {
		return mTestFunctions;
	}

	void GameTestBatch::runBeforeBatchFunction(/*ServerLevel& level*/) {
		if (mBeforeBatchFunction) {
			mBeforeBatchFunction();
		}
	}
} // namespace gametest
