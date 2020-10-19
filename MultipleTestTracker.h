#pragma once

#include <memory>
#include <vector>

namespace gametest {
	class IGameTestListener;
	class GameTestInstance;

	class MultipleTestTracker {
	public:
		MultipleTestTracker();
		MultipleTestTracker(const std::vector<std::shared_ptr<GameTestInstance>>& tests);
		~MultipleTestTracker();

		void addTestToTrack(std::shared_ptr<GameTestInstance> testInstance);
		void addListener(std::shared_ptr<IGameTestListener> listener);

		/* TODO: Add fail only callback listener
		void addFailureListener(final Consumer<GameTestInfo> listener) {
			addListener(new GameTestListener(){
				@Override
				public void testStructureLoaded(final GameTestInfo testInfo) {
				}

				@Override
				public void testPassed(final GameTestInfo testInfo) {
				}

				@Override
				public void testFailed(final GameTestInfo testInfo) {
					listener.accept(testInfo);
				}
				});
		}
		*/

		int getFailedRequiredCount() const;
		int getFailedOptionalCount() const;
		int getDoneCount() const;
		bool hasFailedRequired() const;
		bool hasFailedOptional() const;

		std::vector<std::shared_ptr<GameTestInstance>> getFailedRequired();
		std::vector<std::shared_ptr<GameTestInstance>> getFailedOptional();

		int getTotalCount() const;
		bool isDone() const;

		std::string getProgressBar();

	private:
		static const std::string NOT_STARTED_TEST_CHAR;
		static const std::string ONGOING_TEST_CHAR;
		static const std::string SUCCESSFUL_TEST_CHAR;
		static const std::string FAILED_OPTIONAL_TEST_CHAR;
		static const std::string FAILED_REQUIRED_TEST_CHAR;

		std::vector<std::shared_ptr<GameTestInstance>> mTests;
		std::vector<std::shared_ptr<IGameTestListener>> mListeners;
	};
}