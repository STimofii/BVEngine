// src/BWEngineWin.cpp
#include <bcppul/timer.h>
#include <bcppul/logging.h>
#include "engine/engine.h"

bcppul::Logger* BWELogger = bcppul::getLogger("BWEngineWin");
int main()
{
	//bcppul::SimpleTimer timer;
	bcppul::console_log_level = bcppul::TRACE;
	bcppul::file_log_level = bcppul::NONE;
	
	try {
		bcppul::initLogging();
		BWELogger->info("Starting!!!");
		int code = bulka::Engine::run();
		BWELogger->info("Ending!!!");
		return code;
	}
	catch (std::exception exception) {
		*BWELogger << bcppul::FATAL << "Error in engine!!!: " << exception.what();
		return bulka::Engine::getExitCode();
	}
	
	return 0;
}