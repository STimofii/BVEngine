#pragma once

#include <unordered_map>

namespace bulka {
	class TextureManager {
	private:
		static unsigned int bad_texture;
		static std::unordered_map<const char*, unsigned int> textures;
	protected:
	public:
		static void init();
		static unsigned int getTexture(const char* path);
		static void bindTexture(const char* path);
		static void unbindTexture();
		static void deleteTexture(const char* path);
		static void bindTexture(unsigned int texture);
		static void deleteTexture(unsigned int texture);
		static void finalization();

		static unsigned int loadTexture(const char* path);
		static unsigned int loadTexture(unsigned char* data, int width, int height, int alpha);
	};
}