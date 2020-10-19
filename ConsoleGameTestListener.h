#pragma once

#include "GameTestInstance.h"
#include "IGameTestListener.h"

#include <iostream>

namespace gametest {
	class GameTestInstance;

	class ConsoleGameTestListener : public IGameTestListener {
	public:
		virtual void onTestStructureLoaded(GameTestInstance& test) override {
			std::cout << "onTestStructureLoaded: " << test.getTestName() << std::endl;
		}

		virtual void onTestPassed(GameTestInstance& test) override {
			std::cout << "onTestPassed: " << test.getTestName() << std::endl;
		}

		virtual void onTestFailed(GameTestInstance& test) override {
			std::cout << "onTestFailed: " << test.getTestName() << " - " << test.getError().value().message << std::endl;
		}
	};
} // namespace gametest