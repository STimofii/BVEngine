// src/BWEngineWin.cpp
#include <bcppul/timer.h>
#include "engine/engine.h"

int main()
{
	//bcppul::SimpleTimer timer;

	
	try {
		return bulka::Engine::run();;
	}
	catch (std::exception exception) {
		std::cerr << "Error in engine!!!: " << exception.what() << std::endl;
		return bulka::Engine::getExitCode();
	}
	
	return 0;
}