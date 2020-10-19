#pragma once

#include "BaseGameTestAction.h"
#include "GameTestActionCallback.h"

#include <functional>

namespace gametest {
	class NativeFunctionGameTestAction : public BaseGameTestAction {
	public:
		NativeFunctionGameTestAction(int expectedDelay, GameTestActionCallback fn)
			: BaseGameTestAction(expectedDelay)
			, mFn(std::move(fn)) {
			// TODO: Debug assert mFn
		}

		NativeFunctionGameTestAction(GameTestActionCallback fn)
			: BaseGameTestAction()
			, mFn(std::move(fn)) {
			// TODO: Debug assert mFn
		}

		virtual std::optional<GameTestError> run() override {
			if (mFn) {
				return mFn();
			}

			// TODO: Return nullptr error here?
			return std::nullopt;
		}

	private:
		GameTestActionCallback mFn;
	};
} // namespace gametest
