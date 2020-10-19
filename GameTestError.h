#pragma once

#include <string>

namespace gametest
{
    enum class GameTestErrorType {
        Unknown
    };
    
    struct GameTestError {
       GameTestErrorType type = GameTestErrorType::Unknown;
       std::string message;
	};
} // namespace gametest
