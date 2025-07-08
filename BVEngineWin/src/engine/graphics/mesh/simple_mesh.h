#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include "vertex/vertex3f.h"

namespace bulka {
	class SimpleVertex3fMesh {
	private:
	protected:
	public:
		GLuint VAO = 0;
		GLuint PBO = 0;
		GLuint TBO = 0;
		GLuint IBO = 0;
		GLfloat* positions = nullptr;
		GLuint* indices = nullptr;
		size_t positions_length = 0;
		size_t indices_length = 0;
		SimpleVertex3fMesh(Vertex3f* vertices = nullptr, size_t vertices_length = 0, GLuint* indices = nullptr, size_t indices_length = 0);
		~SimpleVertex3fMesh();

		void update();

		size_t getPositionsLength();
		size_t getIndicesLength();
		GLfloat* getPositions();
		void setVertices(Vertex3f* vertices, size_t length);
		void setPositions(GLfloat* positions, size_t length);
		GLuint* getIndices();
		void setIndices(GLuint* indices, size_t indices_length);

	};
}
