#include "settings.h"

namespace bulka {
	bcppul::Properties Settings::properties("settings.properties");
	std::string Settings::GAME_NAME = "BVEngine";
	void Settings::load()
	{
		properties.load();
	}
	void Settings::init()
	{
		load();
		GAME_NAME = getAndSetIfNotExists("game.name", GAME_NAME);
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
		properties.set(key, value);
	}

	void Settings::set(std::string key, long long value)
	{
		properties.set(key, value);
	}

	void Settings::set(std::string key, double value)
	{
		properties.set(key, value);
	}

	void Settings::set(std::string key, bool value)
	{
		properties.set(key, value);
	}
	void Settings::setIfNotExists(std::string key, std::string value)
	{
		if(properties.get(key).empty()){
			properties.set(key, value);
		}
	}

	void Settings::setIfNotExists(std::string key, long long value)
	{
		if (properties.get(key).empty()) {
			properties.set(key, value);
		}
	}

	void Settings::setIfNotExists(std::string key, double value)
	{
		if (properties.get(key).empty()) {
			properties.set(key, value);
		}
	}

	void Settings::setIfNotExists(std::string key, bool value)
	{
		if (properties.get(key).empty()) {
			properties.set(key, value);
		}
	}

	std::string Settings::getAndSetIfNotExists(std::string key, std::string value)
	{
		std::string temp = properties.get(key);
		if (temp.empty()) {
			properties.set(key, value);
			return value;
		}
		return temp;
	}
	long long Settings::getAndSetIfNotExists(std::string key, long long value)
	{
		if (properties.get(key).empty()) {
			properties.set(key, value);
			return value;
		}
		return properties.getLong(key);
	}
	double Settings::getAndSetIfNotExists(std::string key, double value)
	{
		if (properties.get(key).empty()) {
			properties.set(key, value);
			return value;
		}
		return properties.getDouble(key);
	}
	bool Settings::getAndSetIfNotExists(std::string key, bool value)
	{
		if (properties.get(key).empty()) {
			properties.set(key, value);
			return value;
		}
		return properties.getBool(key);
	}

	void Settings::save()
	{
		properties.save();
	}
	void Settings::finalization() {
		save();
	}
}