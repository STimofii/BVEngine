#include "texture.h"

#include <stb_image/stb_image.h>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace bulka {
	Texture::Texture(const char* path)
	{
		if(path != nullptr){
			loadTexture(path);
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &texture);
	}

	void Texture::loadTexture(const char* path) {
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
			loadTexture(data, width, height, alpha);
			stbi_image_free(data);
		}
		else
		{
			throw std::exception((std::string("Can't load texture ") + std::string(path)).c_str());
		}
	}

	void Texture::loadTexture(unsigned char* data, int width, int height, int alpha)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, alpha, GL_UNSIGNED_BYTE, (GLvoid*)data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::bind() {
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}