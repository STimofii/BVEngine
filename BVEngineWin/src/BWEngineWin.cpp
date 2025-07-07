// src/BWEngineWin.cpp
#include <bcppul/timer.h>
#include "engine/engine.h"

int main()
{
	bcppul::SimpleTimer timer;

	int code = 0;
	try {
		code = bulka::Engine::run();
		return code;
	}
	catch (std::exception exception) {
		std::cerr << "Error in engine!!!: " << exception.what() << std::endl;
		return code;
	}
	
	return 0;
}