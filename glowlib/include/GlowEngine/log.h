#pragma once

#include "spdlog/spdlog.h"

#define GWE_LOGGER_NAME "GlowLogger"

#ifndef GWE_PLATFORM_WINDOWS
	#define GWE_BREAK __debugbreak();
#elif GWE_PLATFORM_LINUX
	#define GWE_BREAK __builtin_debugtrap();
#elif GWE_PLATFORM_MACOS
	#define GWE_BREAK __builtin_trap();
#else 
	#define GWE_BREAK __debugbreak();
#endif

#ifndef GWE_CONFIG_DEBUG
	#define GWE_TRACE(...)		if(spdlog::get(GWE_LOGGER_NAME) != nullptr){spdlog::get(GWE_LOGGER_NAME)->trace(__VA_ARGS__);}
	#define GWE_INFO(...)		if(spdlog::get(GWE_LOGGER_NAME) != nullptr){spdlog::get(GWE_LOGGER_NAME)->info(__VA_ARGS__);}
	#define GWE_DEBUG(...)		if(spdlog::get(GWE_LOGGER_NAME) != nullptr){spdlog::get(GWE_LOGGER_NAME)->debug(__VA_ARGS__);}
	#define GWE_WARN(...)		if(spdlog::get(GWE_LOGGER_NAME) != nullptr){spdlog::get(GWE_LOGGER_NAME)->warn(__VA_ARGS__);}
	#define GWE_ERROR(...)		if(spdlog::get(GWE_LOGGER_NAME) != nullptr){spdlog::get(GWE_LOGGER_NAME)->error(__VA_ARGS__);}
	#define GWE_FATAL(...)		if(spdlog::get(GWE_LOGGER_NAME) != nullptr){spdlog::get(GWE_LOGGER_NAME)->critical(__VA_ARGS__);}
	#define GWE_ASSERT(x, msg)	if(!(x)){} else{ GWE_ERROR("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__); GWE_BREAK;}
#else
	#define GWE_TRACE(...)		void(0)
	#define GWE_INFO(...)		void(0)
	#define GWE_DEBUG(...)		void(0)
	#define GWE_WARN(...)		void(0)
	#define GWE_ERROR(...)		void(0)
	#define GWE_FATAL(...)		void(0)
	#define GWE_ASSERT(x, msg)	void(0)
#endif