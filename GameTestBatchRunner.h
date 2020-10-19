#pragma once

#include "GameTestBatch.h"

#include <memory>
#include <utility>
#include <vector>

namespace gametest {
	class GameTestTicker;
	class GameTestInstance;
	class IGameTestHelperProvider;
	class MultipleTestTracker;

	class GameTestBatchRunner {
	public:
		GameTestBatchRunner(IGameTestHelperProvider& helperProvider, std::vector<GameTestBatch> batches, GameTestTicker& testTicker, int testsPerRow);
		~GameTestBatchRunner();

		/**
		 * This won't be populated until start() has been called
		 */
		const std::vector<std::shared_ptr<GameTestInstance>> getTestInfos();

		void start();

		void runBatch(int batchIndex);

		void testCompleted(GameTestInstance& testInstance);

		void createStructuresForBatch(std::vector<std::shared_ptr<GameTestInstance>>& batch);

	private:
		// TODO
		//private static final Logger LOGGER = LogManager.getLogger();
		//private final BlockPos firstTestNorthWestCorner;
		//private final ServerLevel level;
		//private final Map<GameTestInfo, BlockPos> northWestCorners = Maps.newHashMap();
		//private final BlockPos.MutableBlockPos nextTestNorthWestCorner;

		GameTestTicker& mTestTicker;
		int mTestsPerRow = 0;

		std::vector<std::shared_ptr<GameTestInstance>> mAllTestInstances;
		std::vector<std::pair<GameTestBatch, std::vector<std::shared_ptr<GameTestInstance>>>> mBatches;

		std::unique_ptr<MultipleTestTracker> mCurrentBatchTracker;
		int mCurrentBatchIndex = 0;
	};
} // gametest