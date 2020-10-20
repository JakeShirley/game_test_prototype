#pragma once

#include "GameTestError.h"

#include <optional>

namespace gametest {

	///
	// Base action that is ran in GameTestSequences
	///
	class BaseGameTestAction {
	public:
		BaseGameTestAction(int expectedDelay)
			: mExpectedDelay(expectedDelay) {}
		BaseGameTestAction() {}
		virtual ~BaseGameTestAction() = default;

		std::optional<int> getExpectedDelay() const {
			return mExpectedDelay;
		}

		virtual std::optional<GameTestError> run() = 0; // TODO: Should return error
	private:
		const std::optional<int> mExpectedDelay;
	};
} // namespace gametest
