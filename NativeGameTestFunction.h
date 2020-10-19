#pragma once

#include "BaseGameTestFunction.h"
#include <functional>

namespace gametest
{
    class BaseGameTestHelper;

    class NativeGameTestFunction : public BaseGameTestFunction
    {
    public:
        using NativeGameTestFunctionType = std::function<void(BaseGameTestHelper&)>;

        NativeGameTestFunction(std::string batchName, std::string testName, std::string structureName, int maxTicks, int setupTicks, bool required, NativeGameTestFunctionType fn)
            : BaseGameTestFunction(batchName, testName, structureName, maxTicks, setupTicks, required, 1, 1)
            , mFn(std::move(fn))
        {
        }

        NativeGameTestFunction(std::string batchName, std::string testName, std::string structureName, int maxTicks, int setupTicks, bool required, int requiredSuccesses, int attempts, NativeGameTestFunctionType fn)
            : BaseGameTestFunction(batchName, testName, structureName, maxTicks, setupTicks, required, requiredSuccesses, attempts)
            , mFn(std::move(fn))
        {
        }

        virtual void run(BaseGameTestHelper& helper) override {
            return mFn(helper);
        }

    private:
        NativeGameTestFunctionType mFn;
	};
} // namespace gametest