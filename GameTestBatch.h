#pragma once

#include <functional>
#include <string>

namespace gametest {
	class BaseGameTestFunction;

	class GameTestBatch {
	public:
		static const std::string sDefaultBatchName;
		using BeforeBatchFunction = std::function<void(void)>;

		GameTestBatch(std::string name, std::vector<std::shared_ptr<BaseGameTestFunction>> testFunctions, BeforeBatchFunction beforeBatchFunction = nullptr);

		const std::string& getName();
		const std::vector<std::shared_ptr<BaseGameTestFunction>>& getTestFunctions();

		void runBeforeBatchFunction(/*ServerLevel& level*/);

	private:
		BeforeBatchFunction mBeforeBatchFunction;
		const std::string mName;
		std::vector<std::shared_ptr<BaseGameTestFunction>> mTestFunctions;
	};
} // namespace gametest
