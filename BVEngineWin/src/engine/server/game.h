#pragma once

#include <bcppul/logging.h>

namespace bulka {
	class World;
	class Game {
	private:
		static long long tps;
		static double deltaTime;
		static const long long tpsLimit;
		static const double tpsLimitDelta;

		static bool started;

		static World* world;
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
		static World* getWorld();
	};
}
