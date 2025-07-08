#pragma once

#include <stb_image/stb_image.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace bulka{
	class Texture{
	private:
	protected:
	public:
		unsigned int texture = 0;
		Texture(const char* path = "");
		~Texture();
		void loadTexture(const char* path);

		void bind();
		void unbind();
	};


}
