#include "Log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace d2d
{
    std::shared_ptr<spdlog::logger> Log::mCoreLogger;
    std::shared_ptr<spdlog::logger> Log::mClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        mCoreLogger = spdlog::stdout_color_mt("DRAGO2D_CORE");
        mCoreLogger->set_level(spdlog::level::trace);

        spdlog::set_pattern("%^[%T] %n: %v%$");
        mClientLogger = spdlog::stdout_color_mt("APP");
        mClientLogger->set_level(spdlog::level::trace);
    }


}