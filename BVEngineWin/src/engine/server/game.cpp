#include "game.h"
#include "../engine.h"
#include "world/world.h"

namespace bulka {
	bcppul::Logger* Game::logger = bcppul::getLogger("Game");
	const long long Game::tpsLimit = 20;
	const double Game::tpsLimitDelta = 1.0 / tpsLimit;
	long long Game::tps = 0;
	double Game::deltaTime = 0;
	bool Game::started = false;
	World* Game::world;
	void Game::init() {
		logger->info("Starting game");
		logger->info("Started game");

		logger->info("Starting game loop");
		loop();
	}


	void Game::finalization() {
		logger->info("Finalization game");
		delete world;
	}
	void Game::loop()
	{
		//for (unsigned int i = 0; i < 1000000000; ++i);
		long long timeTickStart;
		long long timeTickElapsed;
		long long timeTPS = Engine::unixTime();
		long long ticks = 0;
		world = new World();
		world->load();

		started = true;
		while (!Engine::isRunning()) {

		}
		while (Engine::isRunning()) {
			timeTickStart = Engine::unixTime();

			do {
				timeTickElapsed = Engine::unixTime() - timeTickStart;
				deltaTime = timeTickElapsed / 1000000000.0;
			} while (tpsLimit != 0 && deltaTime < tpsLimitDelta);
			if (Engine::unixTime() - timeTPS >= 500000000) {
				tps = ticks / 0.5;
				timeTPS = Engine::unixTime();
				ticks = 0;
			}
			++ticks;
			
		}
	}

	long long Game::getTPS() {
		return tps;
	}
	double Game::getDeltaTime() {
		return deltaTime;
	}
	long long Game::getTPSLimit() {
		return tpsLimit;
	}
	double Game::getLimitDelta() {
		return tpsLimitDelta;
	}
	bool Game::isStarted() {
		return started;
	}
	World* Game::getWorld()
	{
		return world;
	}
}
