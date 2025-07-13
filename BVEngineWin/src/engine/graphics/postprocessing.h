#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace bulka {
	class Postprocessing{
	private:
		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint FBO = 0;
		GLuint FBO_Texture = 0;
		GLuint RBO = 0;
	protected:
	public:
		static constexpr float quadVertices[] = {
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f 
		};
		Postprocessing();
		~Postprocessing();

		void init();
		void initFBO();
		void render();
		void bindFBO();
		void unbindFBO();
	};


}
