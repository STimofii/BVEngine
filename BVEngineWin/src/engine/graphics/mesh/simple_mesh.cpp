#include "simple_mesh.h"

namespace bulka {
	SimpleVertex3fMesh::SimpleVertex3fMesh(Vertex3f* vertices, size_t vertices_length, GLuint* indices, size_t indices_length) : 
		indices(indices), indices_length(indices_length)
	{
		setVertices(vertices, vertices_length);
	}
	SimpleVertex3fMesh::~SimpleVertex3fMesh()
	{
		delete[] positions;
		delete[] indices;
	}

	void SimpleVertex3fMesh::update() {
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &PBO);

		glBindBuffer(GL_ARRAY_BUFFER, PBO);
		glBufferData(GL_ARRAY_BUFFER, positions_length * sizeof(float), positions, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);

		if (indices_length == 0) {
			IBO = 0;
		}
		else {
			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_length, indices, GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	size_t SimpleVertex3fMesh::getPositionsLength()
	{
		return positions_length;
	}
	size_t SimpleVertex3fMesh::getIndicesLength()
	{
		return indices_length;
	}

	GLfloat* SimpleVertex3fMesh::getPositions()
	{
		return positions;
	}
	void SimpleVertex3fMesh::setVertices(Vertex3f* vertices, size_t length)
	{
		positions_length = length * 3;
		delete[] this->positions;
		positions = new GLfloat[positions_length];
		for (size_t i = 0; i < length; i++)
		{
			positions[i * 3] = vertices[i].x;
			positions[i * 3 + 1] = vertices[i].y;
			positions[i * 3 + 2] = vertices[i].z;
		}
	}
	void SimpleVertex3fMesh::setPositions(GLfloat* positions, size_t length)
	{
		positions_length = length;
		this->positions = positions;
	}
	GLuint* SimpleVertex3fMesh::getIndices()
	{
		return indices;
	}
	void SimpleVertex3fMesh::setIndices(GLuint* indices, size_t length)
	{
		indices_length = length;
		delete[] this->indices;
		this->indices = indices;
	}
}