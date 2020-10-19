#include "GameTestBatchRunner.h"

#include "GameTestInstance.h"
#include "GameTestRunner.h"
#include "IGameTestListener.h"
#include "MultipleTestTracker.h"

namespace gametest {
	class GameTestBatchRunnerGameTestListener : public IGameTestListener {
	public:
		GameTestBatchRunnerGameTestListener(GameTestBatchRunner& batchRunner)
			: mBatchRunner(batchRunner) {}

		void onTestStructureLoaded(GameTestInstance& /*test*/) override {
		}

		void onTestPassed(GameTestInstance& testInstance) override {
			mBatchRunner.testCompleted(testInstance);
		}

		void onTestFailed(GameTestInstance& testInstance) override {
			mBatchRunner.testCompleted(testInstance);
		}

	private:
		GameTestBatchRunner& mBatchRunner;
	};

	GameTestBatchRunner::GameTestBatchRunner(IGameTestHelperProvider& helperProvider, std::vector<GameTestBatch> batches, GameTestTicker& testTicker, int testsPerRow)
		: mTestTicker(testTicker)
		, mTestsPerRow(testsPerRow) {
		for (auto&& batch : batches) {
			std::vector<std::shared_ptr<GameTestInstance>> instances;
			for (auto&& testFunction : batch.getTestFunctions()) {
				auto testInstance = std::make_shared<GameTestInstance>(*testFunction, helperProvider);
				mAllTestInstances.emplace_back(testInstance);
				instances.emplace_back(std::move(testInstance));
			}

			mBatches.emplace_back(std::make_pair(std::move(batch), std::move(instances)));
		}
	}

	GameTestBatchRunner::~GameTestBatchRunner() = default;

	void GameTestBatchRunner::createStructuresForBatch(std::vector<std::shared_ptr<GameTestInstance>>& batch) {
		// TODO
		/*
		int count = 0;
		AABB rowBounds = new AABB(nextTestNorthWestCorner); // gradually grows to incorporate all structures on the current row

		for (final GameTestInfo testInfo : batch) {
			final BlockPos testNorthWestCorner = new BlockPos(nextTestNorthWestCorner);
			final StructureBlockEntity structureBlock = StructureUtils.spawnStructure(testInfo.getStructureName(), testNorthWestCorner, testInfo.getRotation(), GameTestRunner.PADDING_AROUND_EACH_STRUCTURE, level, true);
			final AABB structureBounds = StructureUtils.getStructureBounds(structureBlock);
			testInfo.setStructureBlockPos(structureBlock.getBlockPos());
			northWestCorners.put(testInfo, new BlockPos(nextTestNorthWestCorner));
			rowBounds = rowBounds.minmax(structureBounds);

			nextTestNorthWestCorner.move((int)structureBounds.getXsize() + GameTestRunner.SPACE_BETWEEN_COLUMNS, 0, 0);

			if (count++ % testsPerRow == testsPerRow - 1) {
				// Time to start a new row
				nextTestNorthWestCorner.move(0, 0, (int)rowBounds.getZsize() + GameTestRunner.SPACE_BETWEEN_ROWS);
				nextTestNorthWestCorner.setX(firstTestNorthWestCorner.getX());
				rowBounds = new AABB(nextTestNorthWestCorner);
			}
		}
		*/
	}

	const std::vector<std::shared_ptr<gametest::GameTestInstance>> GameTestBatchRunner::getTestInfos() {
		return mAllTestInstances;
	}

	void GameTestBatchRunner::start() {
		runBatch(0);
	}

	void GameTestBatchRunner::runBatch(int batchIndex) {
		mCurrentBatchIndex = batchIndex;
		mCurrentBatchTracker = std::make_unique<MultipleTestTracker>();

		if (batchIndex >= static_cast<int>(mBatches.size())) {
			// No more batches to run. We are done!
			return;
		}

		auto& currentBatchEntry = mBatches[mCurrentBatchIndex];
		auto& currentBatch = currentBatchEntry.first;
		auto& testInfosForThisBatch = currentBatchEntry.second;
		createStructuresForBatch(testInfosForThisBatch);
		currentBatch.runBeforeBatchFunction(/*level*/);

		auto& currentBatchName = currentBatch.getName();

		//LOGGER.info("Running test batch '{}' ({} tests)...", currentBatchName, testInfosForThisBatch.size());
		for (auto&& testInstance : testInfosForThisBatch) {
			mCurrentBatchTracker->addTestToTrack(testInstance);
			mCurrentBatchTracker->addListener(std::make_shared<GameTestBatchRunnerGameTestListener>(*this));

			//final BlockPos northWestCorner = northWestCorners.get(testInfo);
			GameTestRunner::runTest(testInstance, mTestTicker);
		}
	}

	void GameTestBatchRunner::testCompleted(GameTestInstance& testInstance) {
		if (mCurrentBatchTracker->isDone()) {
			runBatch(mCurrentBatchIndex + 1);
		}
	}

} // gametest