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



	Block::Block(unsigned short id, std::string name, Face back, Face front, Face left, Face right, Face bottom, Face top) : 
		id(id), name(name), back(back), front(front), left(left), right(right), bottom(bottom), top(top)
	{

	}
	Block::~Block()
	{
	}

	Block::Face::Face(
		float* vertices, unsigned int vertices_length, unsigned int* indices, unsigned int indices_length, 
		float textureX, float textureY, 
		float textureWidth, float textureHeight) : 
		vertices(vertices), vertices_length(vertices_length), indices(indices), indices_length(indices_length),
		textureX(textureX * ONE_BLOCK_TEXTURE_PART_X), 
		textureY(textureY * ONE_BLOCK_TEXTURE_PART_Y),
		textureWidth(textureWidth* ONE_BLOCK_TEXTURE_PART_X), 
		textureHeight(textureHeight * ONE_BLOCK_TEXTURE_PART_Y)
	{
		recalcVertices();
	}
	Block::Face::~Face()
	{

	}
	void Block::Face::recalcVertices()
	{
		for (unsigned int i = 0; i < vertices_length / 5; ++i)
		{
			vertices[i * 5 + 3] = (vertices[i * 5 + 3] * textureWidth + textureX);
			vertices[i * 5 + 4] = (vertices[i * 5 + 4] * textureHeight + textureY);
		}
	}
}