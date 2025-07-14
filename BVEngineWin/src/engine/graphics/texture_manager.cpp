#include "texture_manager.h"

#include <exception>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

namespace bulka {
	std::unordered_map<const char*, unsigned int> TextureManager::textures;
	unsigned int TextureManager::bad_texture = 0;
	void TextureManager::init() {
		bad_texture = loadTexture(new unsigned char[2*2*4]{
					255, 0, 255, 255,
					0, 0, 0, 255, 
					0, 0, 0, 255,
					255, 0, 255, 255
			}, 2, 2, GL_RGBA);
		textures["bad_texture"] = bad_texture;
	}
	unsigned int TextureManager::getTexture(const char* path)
	{
		unsigned int texture = textures[path];
		if (texture == 0) {
			try {
				textures[path] = loadTexture(path);
			}
			catch (std::exception e) {
				std::cerr << e.what() << std::endl;
				textures[path] = bad_texture;
			}
		}
		return textures[path];
	}
	void TextureManager::bindTexture(const char* path)
	{
		glBindTexture(GL_TEXTURE_2D, textures[path]);
	}
	void TextureManager::unbindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void TextureManager::deleteTexture(const char* path)
	{
		glDeleteTextures(1, &textures[path]);
	}
	void TextureManager::bindTexture(unsigned int texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	void TextureManager::deleteTexture(unsigned int texture)
	{
		glDeleteTextures(1, &texture);
	}
	void TextureManager::finalization() {

	}

	unsigned int TextureManager::loadTexture(const char* path) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			int alpha = 0;
			switch (nrChannels) {
			case 1:
				alpha = GL_RED;
				break;
			case 3:
				alpha = GL_RGB;
				break;
			case 4:
				alpha = GL_RGBA;
				break;
			default:
				alpha = GL_RED;
			}
			return loadTexture(data, width, height, alpha);
			stbi_image_free(data);
		}
		else
		{
			throw std::exception((std::string("Can't load texture ") + std::string(path)).c_str());
		}
	}

	unsigned int TextureManager::loadTexture(unsigned char* data, int width, int height, int alpha)
	{
		unsigned int texture = 0;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, alpha, GL_UNSIGNED_BYTE, (GLvoid*)data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}

}