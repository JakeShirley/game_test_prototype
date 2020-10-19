#pragma once

#include <memory>
#include <vector>

namespace gametest {
	class GameTestInstance;

	// Queues and ticks tests
	class GameTestTicker {
	public:
		void add(std::shared_ptr<GameTestInstance> test) {
			mActiveTests.emplace_back(std::move(test));
		}

		void clear() {
			mActiveTests.clear();
		}

		void tick() {
			for (size_t i = 0; i < mActiveTests.size();) {
				auto& test = *mActiveTests[i];

				test.tick();

				if (test.isDone()) {
					mActiveTests.erase(mActiveTests.begin() + i);
				}
				else {
					++i;
				}
			}
		}

		bool empty() const {
			return mActiveTests.empty();
		}

	private:
		std::vector<std::shared_ptr<GameTestInstance>> mActiveTests;
	};
} // namespace gametest
