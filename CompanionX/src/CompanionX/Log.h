#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace CompanionX {

    class COMPANIONX_API Log {
        public:
            static void Init();

            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };  
    
}

// Core Macros
#define CX_CORE_TRACE(...) ::CompanionX::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CX_CORE_INFO(...) ::CompanionX::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CX_CORE_WARN(...) ::CompanionX::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CX_CORE_ERROR(...) ::CompanionX::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CX_CORE_FATAL(...) ::CompanionX::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Macros
#define CX_TRACE(...) ::CompanionX::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CX_INFO(...) ::CompanionX::Log::GetClientLogger()->info(__VA_ARGS__)
#define CX_WARN(...) ::CompanionX::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CX_ERROR(...) ::CompanionX::Log::GetClientLogger()->error(__VA_ARGS__)
#define CX_FATAL(...) ::CompanionX::Log::GetClientLogger()->fatal(__VA_ARGS__)
