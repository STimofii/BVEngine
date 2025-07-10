#include "settings.h"

#include "engine.h"
#include "hero.h"

namespace bulka {
	bcppul::Properties Settings::properties("settings.properties");
	bool Settings::changed = false;

	std::string Settings::GAME_NAME = "BVEngine";
	std::string Settings::FONT = "C:/Windows/Fonts/Arial.ttf";
	float Settings::FOV = 70.0f;
	float Settings::SENSITIVITY = 0.2f;
	float Settings::FPS_LIMIT = 0;
	bool Settings::V_SYNC = false;

	void Settings::load()
	{
		properties.load();
	}
	void Settings::init()
	{
		load();
		
		FONT = getAndSetIfNotExists("game.graphics.font", FONT);
		FPS_LIMIT = getAndSetIfNotExists("game.graphics.fps_limit", FPS_LIMIT);
		Engine::setFPSLimit(FPS_LIMIT);
		V_SYNC = getAndSetIfNotExists("game.graphics.v_sync", V_SYNC);
		Engine::setVSync(V_SYNC);
		FOV = getAndSetIfNotExists("game.graphics.fov", FOV);
		Engine::getHero().getCamera().setFOV(FOV);
		SENSITIVITY = getAndSetIfNotExists("game.graphics.sensitivity", SENSITIVITY);
		Engine::getHero().setSensitivity(SENSITIVITY);
		save();
	}

	std::string Settings::get(std::string key, std::string standard_value)
	{
		return properties.get(key, standard_value);
	}

	long long Settings::getLong(std::string key, long long standard_value)
	{
		return properties.getLong(key, standard_value);
	}

	double Settings::getDouble(std::string key, double standard_value)
	{
		return properties.getDouble(key, standard_value);
	}

	bool Settings::getBool(std::string key, bool standard_value)
	{
		return properties.getBool(key, standard_value);
	}

	void Settings::set(std::string key, std::string value)
	{
		changed = true;
		properties.set(key, value);
	}

	void Settings::set(std::string key, long long value)
	{
		changed = true;
		properties.set(key, value);
	}

	void Settings::set(std::string key, double value)
	{
		changed = true;
		properties.set(key, value);
	}

	void Settings::set(std::string key, bool value)
	{
		changed = true;
		properties.set(key, value);
	}
	void Settings::setIfNotExists(std::string key, std::string value)
	{
		if(properties.get(key).empty()){
			changed = true;
			properties.set(key, value);
		}
	}

	void Settings::setIfNotExists(std::string key, long long value)
	{
		if (properties.get(key).empty()) {
			changed = true;
			properties.set(key, value);
		}
	}

	void Settings::setIfNotExists(std::string key, double value)
	{
		if (properties.get(key).empty()) {
			changed = true;
			properties.set(key, value);
		}
	}

	void Settings::setIfNotExists(std::string key, bool value)
	{
		if (properties.get(key).empty()) {
			changed = true;
			properties.set(key, value);
		}
	}

	std::string Settings::getAndSetIfNotExists(std::string key, std::string value)
	{
		std::string temp = properties.get(key);
		if (temp.empty()) {
			changed = true;
			properties.set(key, value);
			return value;
		}
		return temp;
	}
	long long Settings::getAndSetIfNotExists(std::string key, long long value)
	{
		if (properties.get(key).empty()) {
			changed = true;
			properties.set(key, value);
			return value;
		}
		return properties.getLong(key);
	}
	double Settings::getAndSetIfNotExists(std::string key, double value)
	{
		if (properties.get(key).empty()) {
			changed = true;
			properties.set(key, value);
			return value;
		}
		return properties.getDouble(key);
	}
	bool Settings::getAndSetIfNotExists(std::string key, bool value)
	{
		if (properties.get(key).empty()) {
			changed = true;
			properties.set(key, value);
			return value;
		}
		return properties.getBool(key);
	}

	void Settings::save()
	{
		if(changed){
			properties.save();
			changed = false;
		}
	}
	void Settings::finalization() {
		save();
	}
}