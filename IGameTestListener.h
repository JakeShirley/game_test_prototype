#pragma once

namespace gametest {
	class GameTestInstance;

	class IGameTestListener {
	public:
		virtual ~IGameTestListener() = default;

		virtual void onTestStructureLoaded(GameTestInstance& testInstance) = 0;
		virtual void onTestPassed(GameTestInstance& testInstance) = 0;
		virtual void onTestFailed(GameTestInstance& testInstance) = 0;
	};
} // namespace gametest