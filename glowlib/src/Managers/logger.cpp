#include "GlowEngine/Managers/logger.h"

#include "GlowEngine/log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "memory"

namespace Glow
{
	void Logger::Init()
	{
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("%^[%T] %n: %v%$");

		std::vector<spdlog::sink_ptr> sinks{consoleSink};
		auto logger = std::make_shared<spdlog::logger>(GWE_LOGGER_NAME, sinks.begin(), sinks.end());
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(logger);
	}

	void Logger::Shutdown()
	{
		spdlog::shutdown();
	}
}