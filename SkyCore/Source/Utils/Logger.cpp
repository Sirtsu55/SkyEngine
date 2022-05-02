#include "SkyCore.h"
#include "Utils/Logger.h"


std::shared_ptr<spdlog::logger> Log::CoreLogger;

void Log::Init()
{
	spdlog::set_pattern("%^[%T]: %v%$");

	CoreLogger = spdlog::stdout_color_mt("YUZU");
	CoreLogger->set_level(spdlog::level::trace);
}


