#pragma once

#include <bcppul/properties.h>
#include <bcppul/logging.h>


namespace bulka{
	class Engine;
	class Hero;
	class Settings {
	private:
		static bcppul::Properties properties;
		static bool changed;
	protected:
	public:
		static std::string GAME_NAME;
		static std::string FONT;
		static float FOV;
		static float SENSITIVITY;
		static float FPS_LIMIT;
		static bool V_SYNC;

		static void load();
		static void reload();
		static std::string get(std::string key, std::string standard_value = "");
		static long long getLong(std::string key, long long standard_value = 0);
		static double getDouble(std::string key, double standard_value = 0.0);
		static bool getBool(std::string key, bool standard_value = false);
		static void set(std::string key, std::string value);
		static void set(std::string key, long long value);
		static void set(std::string key, double value);
		static void set(std::string key, bool value);
		static void setIfNotExists(std::string key, std::string value);
		static void setIfNotExists(std::string key, long long value);
		static void setIfNotExists(std::string key, double value);
		static void setIfNotExists(std::string key, bool value);
		static std::string getAndSetIfNotExists(std::string key, std::string value);
		static long long getAndSetIfNotExists(std::string key, long long value);
		static double getAndSetIfNotExists(std::string key, double value);
		static bool getAndSetIfNotExists(std::string key, bool value);
		static void save();
		static void init();
		static void finalization();
	};
}
