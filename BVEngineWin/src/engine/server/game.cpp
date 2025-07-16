#include "game.h"
#include "../engine.h"
#include "world/world.h"

namespace bulka {
	bcppul::Logger* Game::logger = bcppul::getLogger("Game");
	const long long Game::tpsLimit = 20;
	const double Game::tpsLimitDelta = 1.0 / tpsLimit;
	double Game::tps = 0;
	double Game::deltaTime = 0;
	bool Game::started = false;
	World* Game::world;
	void Game::init() {
		logger->info("Starting game");
		world = new World();
		logger->info("Started game");

		logger->info("Starting game loop");
		loop();
	}


	void Game::finalization() {
		logger->info("Finalization game");
		delete world;
		world = nullptr;
	}
	void Game::loop()
	{
		//for (long long i = 0; i < 10000000000L; ++i);
		long long timeTickStart;
		long long timeTickElapsed;
		long long timeTPS = Engine::unixTime();
		long long ticks = 0;
		world->load();

		started = true;
		while (!Engine::isRunning()) {

		}
		while (Engine::isRunning()) {
			timeTickStart = Engine::unixTime();
			world->serverUpdate();


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

	double Game::getTPS() {
		return tps;
	}
	double Game::getDeltaTime() {
		return deltaTime;
	}
	double Game::getTPSLimit() {
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
