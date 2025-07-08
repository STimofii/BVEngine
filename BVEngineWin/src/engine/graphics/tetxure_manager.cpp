#include "texture_manager.h"

namespace bulka {
	std::unordered_map<const char*, Texture*> TextureManager::textures;
	Texture* TextureManager::bad_texture = nullptr;
	void TextureManager::init() {
		bad_texture = new Texture();
		bad_texture->loadTexture(new unsigned char[2*2*4]{
					255, 0, 255, 255,
					0, 0, 0, 255, 
					0, 0, 0, 255,
					255, 0, 255, 255
			}, 2, 2, GL_RGBA);
	}
	Texture* TextureManager::getTexture(const char* path)
	{
		Texture* texture = textures[path];
		if (texture == nullptr) {
			try {
				textures[path] = new Texture(path);
			}
			catch (std::exception e) {
				std::cerr << e.what() << std::endl;
				textures[path] = bad_texture;
			}
		}
		return textures[path];
	}
	void TextureManager::finalization() {

	}
}