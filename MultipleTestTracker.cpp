#include "MultipleTestTracker.h"

#include "GameTestInstance.h"

#include <sstream>

namespace gametest {

	const std::string MultipleTestTracker::sNotStartedTest = " ";
	const std::string MultipleTestTracker::sOnGoingTest = "_";
	const std::string MultipleTestTracker::sSuccessfulTest = "+";
	const std::string MultipleTestTracker::sFailedOptionalTest = "x";
	const std::string MultipleTestTracker::sFailedRequiredTest = "X";

	MultipleTestTracker::MultipleTestTracker() = default;

	MultipleTestTracker::MultipleTestTracker(const std::vector<std::shared_ptr<GameTestInstance>>& tests)
		: mTests(tests) {
	}

	MultipleTestTracker::~MultipleTestTracker() = default;

	void MultipleTestTracker::addTestToTrack(std::shared_ptr<GameTestInstance> testInstance) {
		mTests.emplace_back(testInstance);

		// Add all listeners to new test
		for (auto&& listener : mListeners) {
			testInstance->addListener(listener);
		}
	}

	void MultipleTestTracker::addListener(std::shared_ptr<IGameTestListener> listener) {
		mListeners.emplace_back(listener);

		for (auto&& testInstance : mTests) {
			testInstance->addListener(listener);
		}
	}

	int MultipleTestTracker::getFailedRequiredCount() const {
		int result = 0;
		for (auto&& testInstance : mTests) {
			if (testInstance->hasFailed() && testInstance->isRequired()) {
				result++;
			}
		}
		return result;
	}

	int MultipleTestTracker::getFailedOptionalCount() const {
		int result = 0;
		for (auto&& testInstance : mTests) {
			if (testInstance->hasFailed() && !testInstance->isRequired()) {
				result++;
			}
		}
		return result;
	}

	int MultipleTestTracker::getDoneCount() const {
		int result = 0;
		for (auto&& testInstance : mTests) {
			if (testInstance->isDone()) {
				result++;
			}
		}
		return result;
	}

	bool MultipleTestTracker::hasFailedRequired() const {
		return getFailedRequiredCount() > 0;
	}

	bool MultipleTestTracker::hasFailedOptional() const {
		return getFailedOptionalCount() > 0;
	}

	std::vector<std::shared_ptr<gametest::GameTestInstance>> MultipleTestTracker::getFailedRequired() {
		std::vector<std::shared_ptr<GameTestInstance>> result;
		for (auto&& testInstance : mTests) {
			if (testInstance->hasFailed() && testInstance->isRequired()) {
				result.emplace_back(testInstance);
			}
		}
		return result;
	}

	std::vector<std::shared_ptr<gametest::GameTestInstance>> MultipleTestTracker::getFailedOptional() {
		std::vector<std::shared_ptr<GameTestInstance>> result;
		for (auto&& testInstance : mTests) {
			if (testInstance->hasFailed() && !testInstance->isRequired()) {
				result.emplace_back(testInstance);
			}
		}
		return result;
	}

	int MultipleTestTracker::getTotalCount() const {
		return static_cast<int>(mTests.size());
	}

	bool MultipleTestTracker::isDone() const {
		return getDoneCount() == getTotalCount();
	}

	std::string MultipleTestTracker::getProgressBar() {
		std::stringstream ss;
		ss << "[";
		for (auto&& testInstance : mTests) {
			if (!testInstance->hasStarted()) {
				ss << sNotStartedTest;
			}
			else if (testInstance->hasSucceeded()) {
				ss << sSuccessfulTest;
			}
			else if (testInstance->hasFailed()) {
				ss << (testInstance->isRequired() ? sFailedRequiredTest : sFailedOptionalTest);
			}
			else {
				ss << sOnGoingTest;
			}
		}

		ss << "]";
		return ss.str();
	}

}