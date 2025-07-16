#include "block.h"

#include <iostream>
namespace bulka {
	float Block::Face::defaultVerticesBack[]{
						0.0, 1.0, 0.0, 0.0f, 0.0f,
						1.0, 1.0, 0.0, 1.0f, 0.0f,
						1.0, 0.0, 0.0, 1.0f, 1.0f,
						0.0, 0.0, 0.0, 0.0f, 1.0f,
	};
	unsigned int Block::Face::defaultVerticesBackLength = 20;
	unsigned int Block::Face::defaultIndicesBack[]{
						0, 1, 2,
						2, 3, 0
	};
	unsigned int Block::Face::defaultIndicesBackLength = 6;

	float Block::Face::defaultVerticesFront[]{
						0.0, 0.0, 1.0, 0.0f, 1.0f,
						1.0, 0.0, 1.0, 1.0f, 1.0f,
						1.0, 1.0, 1.0, 1.0f, 0.0f,
						0.0, 1.0, 1.0, 0.0f, 0.0f, 
	};
	unsigned int Block::Face::defaultVerticesFrontLength = 20;
	unsigned int Block::Face::defaultIndicesFront[]{
						0, 1, 2,
						2, 3, 0 
	};
	unsigned int Block::Face::defaultIndicesFrontLength = 6;

	float Block::Face::defaultVerticesLeft[]{
						0.0, 1.0, 1.0, 0.0f, 0.0f, 
						0.0, 1.0, 0.0, 1.0f, 0.0f,
						0.0, 0.0, 0.0, 1.0f, 1.0f,
						0.0, 0.0, 1.0, 0.0f, 1.0f,
	};
	unsigned int Block::Face::defaultVerticesLeftLength = 20;
	unsigned int Block::Face::defaultIndicesLeft[]{
						0, 1, 2,
						2, 3, 0 
	};
	unsigned int Block::Face::defaultIndicesLeftLength = 6;

	float Block::Face::defaultVerticesRight[]{
						1.0, 0.0, 1.0, 0.0f, 1.0f, 
						1.0, 0.0, 0.0, 1.0f, 1.0f,
						1.0, 1.0, 0.0, 1.0f, 0.0f,
						1.0, 1.0, 1.0, 0.0f, 0.0f,
	};
	unsigned int Block::Face::defaultVerticesRightLength = 20;
	unsigned int Block::Face::defaultIndicesRight[]{
						0, 1, 2,
						2, 3, 0 
	};
	unsigned int Block::Face::defaultIndicesRightLength = 6;

	float Block::Face::defaultVerticesBottom[]{
						0.0, 0.0, 0.0, 0.0f, 1.0f,
						1.0, 0.0, 0.0, 1.0f, 1.0f,
						1.0, 0.0, 1.0, 1.0f, 0.0f,
						0.0, 0.0, 1.0, 0.0f, 0.0f, 
	};
	unsigned int Block::Face::defaultVerticesBottomLength = 20;
	unsigned int Block::Face::defaultIndicesBottom[]{
						0, 1, 2,
						2, 3, 0 
	};
	unsigned int Block::Face::defaultIndicesBottomLength = 6;

	float Block::Face::defaultVerticesTop[]{
						0.0, 1.0, 1.0, 0.0f, 0.0f,
						1.0, 1.0, 1.0, 1.0f, 0.0f,
						1.0, 1.0, 0.0, 1.0f, 1.0f,
						0.0, 1.0, 0.0, 0.0f, 1.0f,
	};
	unsigned int Block::Face::defaultVerticesTopLength = 20;
	unsigned int Block::Face::defaultIndicesTop[]{
						0, 1, 2,
						2, 3, 0 
	};
	unsigned int Block::Face::defaultIndicesTopLength = 6;

	Block::Face Block::defaultFaceBack = Face(
		Face::defaultVerticesBack, Face::defaultVerticesBottomLength,
		Face::defaultIndicesBack, Face::defaultIndicesBackLength,
		0.0f, 0.0f,
		1.0f, 1.0f,
		glm::vec3{ 0, 0, -1 }
	);
	Block::Face Block::defaultFaceFront = Face(
		Face::defaultVerticesFront, Face::defaultVerticesFrontLength,
		Face::defaultIndicesFront, Face::defaultIndicesFrontLength,
		0.0f, 0.0f,
		1.0f, 1.0f,
		glm::vec3{ 0, 0, 1 }
	);
	Block::Face Block::defaultFaceLeft = Face(
		Face::defaultVerticesLeft, Face::defaultVerticesLeftLength,
		Face::defaultIndicesLeft, Face::defaultIndicesLeftLength,
		0.0f, 0.0f,
		1.0f, 1.0f,
		glm::vec3{ -1, 0, 0 }
	);
	Block::Face Block::defaultFaceRight = Face(
		Face::defaultVerticesRight, Face::defaultVerticesRightLength,
		Face::defaultIndicesRight, Face::defaultIndicesRightLength,
		0.0f, 0.0f,
		1.0f, 1.0f,
		glm::vec3{ 1, 0, 0 }
	);
	Block::Face Block::defaultFaceBottom = Face(
		Face::defaultVerticesBottom, Face::defaultVerticesBottomLength,
		Face::defaultIndicesBottom, Face::defaultIndicesBottomLength,
		0.0f, 0.0f,
		1.0f, 1.0f,
		glm::vec3{ 0, -1, 0 }
	);
	Block::Face Block::defaultFaceTop = Face(
		Face::defaultVerticesTop, Face::defaultVerticesTopLength,
		Face::defaultIndicesTop, Face::defaultIndicesTopLength,
		0.0f, 0.0f,
		1.0f, 1.0f,
		glm::vec3{ 0, 1, 0 }
	);

	Block::Block(unsigned short id, std::string name, bool hasAlpha, Face back, Face front, Face left, Face right, Face bottom, Face top) : 
		id(id), name(name), hasAlpha(hasAlpha), back(back), front(front), left(left), right(right), bottom(bottom), top(top)
	{

	}
	Block::~Block()
	{
	}

	Block::Face::Face(
		float* vertices, unsigned int vertices_length, unsigned int* indices, unsigned int indices_length, 
		float textureX, float textureY, 
		float textureWidth, float textureHeight, glm::vec3 normal) : 
		vertices(vertices), vertices_length(vertices_length), indices(indices), indices_length(indices_length),
		textureX(textureX), 
		textureY(textureY),
		textureWidth(textureWidth), 
		textureHeight(textureHeight),
		normal(normal)
	{
		//recalcVertices();
	}
	Block::Face::Face(const Face& other) : 
		indices_length(other.indices_length), vertices_length(other.vertices_length),
		textureX(other.textureX), textureY(other.textureY),
		textureWidth(other.textureWidth), textureHeight(other.textureHeight), normal(other.normal)
	{
		vertices = new float[vertices_length];
		for (unsigned int i = 0; i < vertices_length; i++)
		{
			vertices[i] = other.vertices[i];
		}
		indices = new unsigned int[indices_length];
		for (unsigned int i = 0; i < indices_length; i++)
		{
			indices[i] = other.indices[i];
		}
	}
	Block::Face::~Face()
	{

	}
	Block::Face* Block::Face::setVertices(float* vertices, unsigned int vertices_length)
	{
		this->vertices = vertices;
		this->vertices_length = vertices_length;
		return this;
	}
	Block::Face* Block::Face::setIndices(unsigned int* indices, unsigned int indices_length)
	{
		this->indices = indices;
		this->indices_length = indices_length;
		return this;
	}
	Block::Face* Block::Face::setTextureX(float val)
	{
		textureX = val;
		return this;
	}
	Block::Face* Block::Face::setTextureY(float val)
	{
		textureY = val;
		return this;
	}
	Block::Face* Block::Face::setTextureWidth(float val)
	{
		textureWidth = val;
		return this;
	}
	Block::Face* Block::Face::setTextureHeight(float val)
	{
		textureHeight = val;
		return this;
	}
	Block::Face* Block::Face::recalcVertices()
	{
		for (unsigned int i = 0; i < vertices_length / 5; ++i)
		{
			vertices[i * 5 + 3] = ((vertices[i * 5 + 3] * textureWidth + textureX) * ONE_BLOCK_TEXTURE_PART_X);
			vertices[i * 5 + 4] = ((vertices[i * 5 + 4] * textureHeight + textureY) * ONE_BLOCK_TEXTURE_PART_Y);
		}
		return this;
	}
}