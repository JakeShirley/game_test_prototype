#pragma once

#include <memory>

namespace gametest
{
    class BaseGameTestHelper;
    class GameTestInstance;

    class IGameTestHelperProvider
    {
    public:
        virtual ~IGameTestHelperProvider() = default;
        virtual std::unique_ptr<BaseGameTestHelper> createGameTestHelper(GameTestInstance &testInstance) = 0;
	};
} // namespace gametest
