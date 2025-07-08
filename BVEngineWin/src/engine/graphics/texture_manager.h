#pragma once

#include <unordered_map>
#include <exception>
#include <iostream>
#include <GL/glew.h>
#include "mesh/texture.h"
namespace bulka {
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