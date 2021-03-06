#pragma once

#include "Enigma/Core.h"
#include "spdlog/spdlog.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace Enigma {

	class Log {
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_ClientLogger;
		static Ref<spdlog::logger> s_CoreLogger;

	};

}

#if defined(ENGM_DEBUG) || defined(ENGM_RELEASE)

//assertion macros
#ifdef ENGM_ENABLE_ASSERT
	#define ENGM_CORE_ASSERT(condition,...)   if(!condition){\
										      ::Enigma::Log::GetCoreLogger()->critical(__VA_ARGS__);\
										      __debugbreak(); }
	#define ENGM_ASSERT(condition,...)        if(!condition){\
									          ::Enigma::Log::GetClientLogger()->critical(__VA_ARGS__);\
										      __debugbreak(); }
#else
	#define ENGM_CORE_ASSERT(condition,...)
	#define ENGM_ASSERT(condition,...)
#endif
//Core logging macros
	#define ENGM_CORE_FATAL(...)              ::Enigma::Log::GetCoreLogger()->critical(__VA_ARGS__)
	#define ENGM_CORE_ERROR(...)              ::Enigma::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define ENGM_CORE_WARN(...)               ::Enigma::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define ENGM_CORE_INFO(...)               ::Enigma::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define ENGM_CORE_TRACE(...)              ::Enigma::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client logging macros
	#define ENGM_FATAL(...)                   ::Enigma::Log::GetClientLogger()->critical(__VA_ARGS__)
	#define ENGM_ERROR(...)	                  ::Enigma::Log::GetClientLogger()->error(__VA_ARGS__)
	#define ENGM_WARN(...)	                  ::Enigma::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define ENGM_INFO(...)	                  ::Enigma::Log::GetClientLogger()->info(__VA_ARGS__)
	#define ENGM_TRACE(...)	                  ::Enigma::Log::GetClientLogger()->trace(__VA_ARGS__)

#else
	//Core logging macros
//	#define ENGM_CORE_FATAL(...)
	#define ENGM_CORE_ERROR(...)
	#define ENGM_CORE_WARN(...)
	#define ENGM_CORE_INFO(...)
	#define ENGM_CORE_TRACE(...)

	//Client logging macros
//	#define ENGM_FATAL(...)
	#define ENGM_ERROR(...)
	#define ENGM_WARN(...)
	#define ENGM_INFO(...)
	#define ENGM_TRACE(...)
#endif
