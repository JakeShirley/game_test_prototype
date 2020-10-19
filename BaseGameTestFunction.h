#pragma once

#include <string>

namespace gametest
{
    class BaseGameTestHelper;

    class BaseGameTestFunction
    {
    public:
        BaseGameTestFunction(std::string batchName, std::string testName, std::string structureName, int maxTicks, int setupTicks, bool required)
            : BaseGameTestFunction(batchName, testName, structureName, maxTicks, setupTicks, required, 1, 1)
        {
        }

        BaseGameTestFunction(std::string batchName, std::string testName, std::string structureName, int maxTicks, int setupTicks, bool required, int requiredSuccesses, int attempts)
            : mBatchName(std::move(batchName))
            , mTestName(std::move(testName))
            , mStructureName(std::move(structureName))
            , mMaxTicks(maxTicks)
            , mRequired(required)
            , mRequiredSuccesses(requiredSuccesses)
            , mMaxAttempts(attempts)
            , mSetupTicks(setupTicks)
            //, mRotation(rotation)
        {
        }

        virtual void run(BaseGameTestHelper& helper) = 0;

        const std::string& getTestName() const {
            return mTestName;
        }

        int getMaxTicks() const {
            return mMaxTicks;
        }

		int getSetupTicks() const {
			return mSetupTicks;
		}

		const std::string& getBatchName() const {
			return mBatchName;
		}

		bool isRequired() const {
			return mRequired;
		}

    private:
        // TODO:
        //const Rotation mRotation;

        const std::string mBatchName;
        const std::string mTestName;
        const std::string mStructureName;
        const bool mRequired = false;
        const int mMaxAttempts = 0;
        const int mRequiredSuccesses = 0;
        const int mMaxTicks = 0;
        const int mSetupTicks = 0;
	};
} // namespace gametest