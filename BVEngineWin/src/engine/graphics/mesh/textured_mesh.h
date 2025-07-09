#pragma once

#include <vector>
#include <iostream>
#include <exception>
#include <GL/glew.h>
#include "vertex/vertex3f.h"
#include "texture.h"

namespace bulka {
	class TexturedMesh {
	private:
	protected:
	public:
		GLuint VAO = 0;
		GLuint PBO = 0;
		GLuint IBO = 0;
		GLfloat* positions = nullptr;
		GLuint* indices = nullptr;
		size_t positions_length = 0;
		size_t indices_length = 0;
		Texture* texture;
		TexturedMesh(Vertex5f* vertices = nullptr, size_t vertices_length = 0, GLuint* indices = nullptr, size_t indices_length = 0, Texture* texture = nullptr);
		~TexturedMesh();

		void update();

		size_t getPositionsLength();
		size_t getIndicesLength();
		GLfloat* getPositions();
		void setVertices(Vertex5f* vertices, size_t length);
		void setPositions(GLfloat* positions, size_t length);
		GLuint* getIndices();
		void setIndices(GLuint* indices, size_t indices_length);
		Texture* getTexture();
		void setTexture(Texture* texture);
	};
}
