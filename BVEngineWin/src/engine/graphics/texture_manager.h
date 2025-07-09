#pragma once

#include <unordered_map>

namespace bulka {
	class Texture;
	class TextureManager {
	private:
		static Texture* bad_texture;
		static std::unordered_map<const char*, Texture*> textures;
	protected:
	public:
		static void init();
		static Texture* getTexture(const char* path);
		static void finalization();
	};
}