#include "textured_mesh.h"

namespace bulka {
	TexturedMesh::TexturedMesh()
	{
	}
	TexturedMesh::TexturedMesh(float* vertices, size_t vertices_length, GLuint* indices, size_t indices_length, GLuint texture) :
		texture(texture)
	{
		update(vertices, vertices_length, indices, indices_length);
	}
	TexturedMesh::~TexturedMesh()
	{
		glDeleteBuffers(1, &PBO);
		glDeleteBuffers(1, &IBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void TexturedMesh::update(float* vertices, size_t vertices_length, GLuint* indices, size_t indices_length) {
		this->vertices_length = vertices_length;
		this->indices_length = indices_length;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &PBO);

		glBindBuffer(GL_ARRAY_BUFFER, PBO);
		glBufferData(GL_ARRAY_BUFFER, vertices_length * sizeof(float), vertices, GL_STATIC_DRAW);
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
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	size_t TexturedMesh::getVerticesLength()
	{
		return vertices_length;
	}
	size_t TexturedMesh::getIndicesLength()
	{
		return indices_length;
	}
	GLuint TexturedMesh::getTexture()
	{
		return texture;
	}
	void TexturedMesh::setTexture(GLuint texture)
	{
		this->texture = texture;
	}
}