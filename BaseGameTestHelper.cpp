#include "BaseGameTestHelper.h"

#include "GameTestInstance.h"
#include "GameTestSequence.h"

namespace gametest
{
    
	BaseGameTestHelper::BaseGameTestHelper(GameTestInstance &testInstance) 
		: mTestInstance(testInstance) {
	}

	void BaseGameTestHelper::succeed() {
		mTestInstance.succeed();
	}

	void BaseGameTestHelper::succeedIf(GameTestActionCallback fn) {
		mTestInstance.createSequence()
			.thenWait(0, std::move(fn))
			.thenSucceed();
	}

} // namespace gametest