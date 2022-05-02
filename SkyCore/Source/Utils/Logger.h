#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


class Log
{
private:
	Log() = delete;
	~Log() = delete;


	static std::shared_ptr<spdlog::logger> CoreLogger;
public:

	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }



};

