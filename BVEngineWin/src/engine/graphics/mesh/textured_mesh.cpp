#include "textured_mesh.h"

#include "vertex/vertex5f.h"
#include "texture.h"

namespace bulka {
	TexturedMesh::TexturedMesh(Vertex5f* vertices, size_t vertices_length, GLuint* indices, size_t indices_length, Texture* texture) : 
		indices(indices), indices_length(indices_length), texture(texture)
	{
		setVertices(vertices, vertices_length);
	}
	TexturedMesh::~TexturedMesh()
	{
		delete[] positions;
		delete[] indices;
		glDeleteBuffers(1, &PBO);
		glDeleteBuffers(1, &IBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void TexturedMesh::update() {
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &PBO);

		glBindBuffer(GL_ARRAY_BUFFER, PBO);
		glBufferData(GL_ARRAY_BUFFER, positions_length * sizeof(float), positions, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		if (indices_length == 0) {
			IBO = 0;
		}
		else {
			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_length * sizeof(GLuint), indices, GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	size_t TexturedMesh::getPositionsLength()
	{
		return positions_length;
	}
	size_t TexturedMesh::getIndicesLength()
	{
		return indices_length;
	}

	GLfloat* TexturedMesh::getPositions()
	{
		return positions;
	}
	void TexturedMesh::setVertices(Vertex5f* vertices, size_t length)
	{
		positions_length = length * 5;
		delete[] this->positions;
		positions = new GLfloat[positions_length];
		for (size_t i = 0; i < length; i++)
		{
			int j = i * 5;
			positions[j] = vertices[i].x;
			positions[j + 1] = vertices[i].y;
			positions[j + 2] = vertices[i].z;
			positions[j + 3] = vertices[i].u;
			positions[j + 4] = vertices[i].v;
		}
		delete[] vertices;
	}
	void TexturedMesh::setPositions(GLfloat* positions, size_t length)
	{
		positions_length = length;
		this->positions = positions;
	}
	GLuint* TexturedMesh::getIndices()
	{
		return indices;
	}
	void TexturedMesh::setIndices(GLuint* indices, size_t length)
	{
		indices_length = length;
		delete[] this->indices;
		this->indices = indices;
	}
	Texture* TexturedMesh::getTexture()
	{
		return texture;
	}
	void TexturedMesh::setTexture(Texture* texture)
	{
		this->texture = texture;
	}
}