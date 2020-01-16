#pragma once

#include <spdlog/spdlog.h>

#include "Core.hpp"

namespace d2d
{
	class D2D_API Log
    {
    private:
        static std::shared_ptr<spdlog::logger> mCoreLogger;
        static std::shared_ptr<spdlog::logger> mClientLogger;

    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> & GetCoreLogger() { return mCoreLogger; }
        inline static std::shared_ptr<spdlog::logger> & GetClientLogger() { return mClientLogger; }
    };
}

#define D2D_LOG_CORE_TRACE(...)       d2d::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define D2D_LOG_CORE_INFO(...)        d2d::Log::GetCoreLogger()->info(__VA_ARGS__)
#define D2D_LOG_CORE_WARN(...)        d2d::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define D2D_LOG_CORE_ERROR(...)       d2d::Log::GetCoreLogger()->error(__VA_ARGS__)
#define D2D_LOG_CORE_CRITICAL(...)    ::d2d::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define D2D_LOG_TRACE(...)       d2d::Log::GetClientLogger()->trace(__VA_ARGS__)
#define D2D_LOG_INFO(...)        d2d::Log::GetClientLogger()->info(__VA_ARGS__)
#define D2D_LOG_WARN(...)        d2d::Log::GetClientLogger()->warn(__VA_ARGS__)
#define D2D_LOG_ERROR(...)       d2d::Log::GetClientLogger()->error(__VA_ARGS__)
#define D2D_LOG_CRITICAL(...)    d2d::Log::GetClientLogger()->critical(__VA_ARGS__)