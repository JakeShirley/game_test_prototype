#pragma once

#include "GameTestError.h"
#include <functional>
#include <optional>

namespace gametest
{
    using GameTestActionCallback = std::function<std::optional<GameTestError>(void)>;
} // namespace gametest
