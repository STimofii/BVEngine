#pragma once

#include <bcppul/logging.h>

namespace bulka {
	class Game {
	private:
		static long long tps;
		static double deltaTime;
		static const long long tpsLimit;
		static const double tpsLimitDelta;

		static bool started;
	protected:
	public:
		static bcppul::Logger* logger;
		static void init();
		static void finalization();
		static void loop();
		static void update();

		static long long getTPS();
		static double getDeltaTime();
		static long long getTPSLimit();
		static double getLimitDelta();
		static bool isStarted();
	};
}
