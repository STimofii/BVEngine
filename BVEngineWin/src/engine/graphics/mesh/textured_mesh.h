#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace bulka {
	class TexturedMesh {
	private:
	protected:
	public:
		GLuint VAO = 0;
		GLuint PBO = 0;
		GLuint IBO = 0;
		size_t vertices_length = 0;
		size_t indices_length = 0;
		GLuint texture = 0;
		TexturedMesh();
		TexturedMesh(float* vertices, size_t vertices_length, GLuint* indices = nullptr, size_t indices_length = 0, GLuint texture = 0);
		~TexturedMesh();

		void update(float* vertices, size_t vertices_length, GLuint* indices = nullptr, size_t indices_length = 0);

		size_t getVerticesLength();
		size_t getIndicesLength();
		GLuint getTexture();
		void setTexture(GLuint texture);
	};
}
