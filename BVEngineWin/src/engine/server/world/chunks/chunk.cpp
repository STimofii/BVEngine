#include "chunk.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <iomanip>

#include "../../blocks/block.h"
#include "../../../engine.h"
#include "../../../graphics/shader_manager.h"
#include "../../blocks/blocks_manager.h"
namespace bulka {
	bcppul::Logger* Chunk::logger = bcppul::getLogger("Chunk");
	Chunk::Chunk(glm::ivec2 position) : position(position)
	{
		blockStartPosition.x = position.x * CHUNK_SIZE_X;
		blockStartPosition.y = position.y * CHUNK_SIZE_Z;
		blocks = new unsigned short[CHUNK_VOLUME] {};
	}
	Chunk::~Chunk()
	{
	}

	void Chunk::generate() {
		for (unsigned int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (unsigned int x = 0; x < CHUNK_SIZE_X; x++)
			{
				for (unsigned int z = 0; z < CHUNK_SIZE_Z; z++)
				{
					unsigned int i = ((y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + x * CHUNK_SIZE_Z) + z;
					if (y < 5) {
						blocks[i] = 1;

					}
				}
			}
		}
	}
	void Chunk::createMeshes() {
		if (!Engine::isRunning()) {
			return;
		}
		*logger << bcppul::TRACE << "Loading chunk X:" << position.x << "; z:" << position.y;
		for (unsigned int sub_chunk_i = 0; sub_chunk_i < SUB_CHUNKS_IN_CHUNK; sub_chunk_i++)
		{
			SubChunk& subChunk = sub_chunks[sub_chunk_i];
			std::vector<float> vertices;
			std::vector<unsigned int> indices;

			unsigned int index = 0;

			for (unsigned int y = sub_chunk_i * SUB_CHUNK_SIZE_Y; y < SUB_CHUNK_SIZE_Y * (sub_chunk_i + 1); ++y)
			{
				for (unsigned int x = 0; x < CHUNK_SIZE_X; ++x)
				{
					for (unsigned int z = 0; z < CHUNK_SIZE_Z; ++z)
					{
						unsigned int bpos = ((y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + x * CHUNK_SIZE_Z) + z;
						unsigned short block = blocks[bpos];
						if (block == 0) {
							continue;
						}
						Block* prefab = BlocksManager::getBlock(block);
						Block::Face& back = prefab->back;
						Block::Face& front = prefab->front;
						Block::Face& left = prefab->left;
						Block::Face& right = prefab->right;
						Block::Face& bottom = prefab->bottom;
						Block::Face& top = prefab->top;
						for (unsigned int i = 0; i < back.vertices_length / 5; i++)
						{
							vertices.push_back(back.vertices[i * 5 + 0] + x);
							vertices.push_back(back.vertices[i * 5 + 1] + y);
							vertices.push_back(back.vertices[i * 5 + 2] + z);
							vertices.push_back(back.vertices[i * 5 + 3]);
							vertices.push_back(back.vertices[i * 5 + 4]);
						}
						
						for (unsigned int i = 0; i < back.indices_length; i++)
						{
							indices.push_back(back.indices[i] + index);
						}
						index += back.vertices_length / 5;
						for (unsigned int i = 0; i < front.vertices_length / 5; i++)
						{
							vertices.push_back(front.vertices[i * 5 + 0] + x);
							vertices.push_back(front.vertices[i * 5 + 1] + y);
							vertices.push_back(front.vertices[i * 5 + 2] + z);
							vertices.push_back(front.vertices[i * 5 + 3]);
							vertices.push_back(front.vertices[i * 5 + 4]);
						}
						for (unsigned int i = 0; i < front.indices_length; i++)
						{
							indices.push_back(front.indices[i] + index);
						}
						index += front.vertices_length / 5;
						for (unsigned int i = 0; i < left.vertices_length / 5; i++)
						{
							vertices.push_back(left.vertices[i * 5 + 0] + x);
							vertices.push_back(left.vertices[i * 5 + 1] + y);
							vertices.push_back(left.vertices[i * 5 + 2] + z);
							vertices.push_back(left.vertices[i * 5 + 3]);
							vertices.push_back(left.vertices[i * 5 + 4]);
						}
						for (unsigned int i = 0; i < left.indices_length; i++)
						{
							indices.push_back(left.indices[i] + index);
						}
						index += left.vertices_length / 5;
						for (unsigned int i = 0; i < right.vertices_length / 5; i++)
						{
							vertices.push_back(right.vertices[i * 5 + 0] + x);
							vertices.push_back(right.vertices[i * 5 + 1] + y);
							vertices.push_back(right.vertices[i * 5 + 2] + z);
							vertices.push_back(right.vertices[i * 5 + 3]);
							vertices.push_back(right.vertices[i * 5 + 4]);
						}
						for (unsigned int i = 0; i < right.indices_length; i++)
						{
							indices.push_back(right.indices[i] + index);
						}
						index += right.vertices_length / 5;
						for (unsigned int i = 0; i < bottom.vertices_length / 5; i++)
						{
							vertices.push_back(bottom.vertices[i * 5 + 0] + x);
							vertices.push_back(bottom.vertices[i * 5 + 1] + y);
							vertices.push_back(bottom.vertices[i * 5 + 2] + z);
							vertices.push_back(bottom.vertices[i * 5 + 3]);
							vertices.push_back(bottom.vertices[i * 5 + 4]);
						}
						for (unsigned int i = 0; i < bottom.indices_length; i++)
						{
							indices.push_back(bottom.indices[i] + index);
						}
						index += bottom.vertices_length / 5;
						for (unsigned int i = 0; i < top.vertices_length / 5; i++)
						{
							vertices.push_back(top.vertices[i * 5 + 0] + x);
							vertices.push_back(top.vertices[i * 5 + 1] + y);
							vertices.push_back(top.vertices[i * 5 + 2] + z);
							vertices.push_back(top.vertices[i * 5 + 3]);
							vertices.push_back(top.vertices[i * 5 + 4]);
						}
						for (unsigned int i = 0; i < top.indices_length; i++)
						{
							indices.push_back(top.indices[i] + index);
						}
						index += top.vertices_length / 5;
					}
				}
			}
			//for (unsigned int i = 0; i < vertices.size() / 5; i++)
			//{
			//	std::cout << "XYZ: " << vertices[i * 5] << "; " << vertices[i * 5 + 1] << "; " << vertices[i * 5 + 2] << "; UV: " << vertices[i * 5 + 3] << "; " << vertices[i * 5 + 4] << std::endl;
			//}
			//for (unsigned int i = 0; i < indices.size() / 6; i++)
			//{
			//	std::cout << indices[i * 6 + 0] << ", " << indices[i * 6 + 1] << ", " << indices[i * 6 + 2] << "\t" 
			//		<< indices[i * 6 + 3] << ", " << indices[i * 6 + 4] << ", " << indices[i * 6 + 5] << std::endl;
			//}

			if (vertices.size() == 0 || indices.size() == 0) {
				subChunk.VAO = 0;
				subChunk.IBO = 0;
				subChunk.VBO = 0;
				subChunk.vertices_length = 0;
				subChunk.indices_length = 0;
				continue;
			}
			unsigned int VAO = 0;
			unsigned int VBO = 0;
			unsigned int IBO = 0;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			subChunk.VAO = VAO;
			subChunk.IBO = IBO;
			subChunk.VBO = VBO;
			subChunk.vertices_length = vertices.size();
			subChunk.indices_length = indices.size();
		}
	}
	void Chunk::deleteMeshes()
	{
		for (unsigned int i = 0; i < SUB_CHUNKS_IN_CHUNK; i++)
		{
			glDeleteBuffers(1, &sub_chunks[i].VBO);
			glDeleteBuffers(1, &sub_chunks[i].IBO);
			glDeleteVertexArrays(1, &sub_chunks[i].VAO);
		}
	}
	void Chunk::update() {

	}
	void Chunk::render() {
		ShaderManager::chunkShader.uniform2iv("chunkPosition", blockStartPosition);
		for (unsigned int i = 0; i < SUB_CHUNKS_IN_CHUNK; i++)
		{
			if (sub_chunks[i].VAO == 0) {
				continue;
			}
			glBindVertexArray(sub_chunks[i].VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sub_chunks[i].IBO);
			glDrawElements(GL_TRIANGLES, sub_chunks[i].indices_length, GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

	}

	void Chunk::finalization() {
		delete[] blocks;
		deleteMeshes();
	}
}