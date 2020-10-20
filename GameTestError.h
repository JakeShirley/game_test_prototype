#pragma once

#include <string>

namespace gametest {
	enum class GameTestErrorType {
		Unknown
	};

	///
	// A class that captures an error that occured somewhere in GameTest
	///
	struct GameTestError {
		GameTestErrorType type = GameTestErrorType::Unknown;
		std::string message;
	};
} // namespace gametest
