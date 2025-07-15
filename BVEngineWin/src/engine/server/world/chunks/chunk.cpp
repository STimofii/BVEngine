#include "chunk.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "../../blocks/block.h"
#include "../../../engine.h"
#include "../../../graphics/shader_manager.h"
#include "../../blocks/blocks_manager.h"
#include "../world.h"
namespace bulka {
	bcppul::Logger* Chunk::logger = bcppul::getLogger("Chunk");
	Chunk::Chunk(World* world, glm::ivec2 position) : position(position), world(world)
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
		updateMeshes = 0xFFFF;
	}
	void Chunk::createMesh(unsigned int sub_chunk_i)
	{
		updateMeshes = updateMeshes & ~(1 << sub_chunk_i);
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
					unsigned short blockID = blocks[bpos] & 0x0FFF;
					unsigned short blockState = blocks[bpos] & 0xF000;
					if (blockID == 0) {
						continue;
					}
					Block* prefab = BlocksManager::getBlock(blockID);
					char neighbors = 0;
					if (z != 0) {
						if (isBlockPrefabHasAlpha(x, y, z - 1)) {
							neighbors = neighbors | 0b00000001;
						}
					}
					else {
						if (position.y == -world->getRenderDistance()) {
							neighbors = (RENDER_BLOCKS_ON_WORLD_EDGE ? neighbors | 0b00000001 : neighbors | 0b00000000);
						}
						else {
							neighbors = neighbors | world->getChunk(position.x, position.y - 1)->getBlockPrefab(x, y, CHUNK_SIZE_Z - 1)->hasAlpha;
						}
					}

					if (z != CHUNK_SIZE_Z - 1) {
						if (isBlockPrefabHasAlpha(x, y, z + 1)) {
							neighbors = neighbors | 0b00000010;
						}
					}
					else {
						if (position.y == world->getRenderDistance()) {
							neighbors = (RENDER_BLOCKS_ON_WORLD_EDGE ? neighbors | 0b00000010 : neighbors | 0b00000000);
						}
						else {
							neighbors = neighbors | (world->getChunk(position.x, position.y + 1)->getBlockPrefab(x, y, 0)->hasAlpha) << 1;
						}
					}
					if (x != 0) {
						if (isBlockPrefabHasAlpha(x - 1, y, z)) {
							neighbors = neighbors | 0b00000100;
						}
					}
					else {
						if (position.x == -world->getRenderDistance()) {
							neighbors = (RENDER_BLOCKS_ON_WORLD_EDGE ? neighbors | 0b00000100 : neighbors | 0b00000000);
						}
						else {
							neighbors = neighbors | (world->getChunk(position.x - 1, position.y)->getBlockPrefab(CHUNK_SIZE_X - 1, y, z)->hasAlpha) << 2;
						}
					}
					if (x != CHUNK_SIZE_X - 1) {
						if (isBlockPrefabHasAlpha(x + 1, y, z)) {
							neighbors = neighbors | 0b00001000;
						}
					}
					else {
						if (position.x == world->getRenderDistance()) {
							neighbors = (RENDER_BLOCKS_ON_WORLD_EDGE ? neighbors | 0b00001000 : neighbors | 0b00000000);
						}
						else {
							neighbors = neighbors | (world->getChunk(position.x + 1, position.y)->getBlockPrefab(0, y, z)->hasAlpha) << 3;
						}
					}


					if (y != 0) {
						if (isBlockPrefabHasAlpha(x, y - 1, z)) {
							neighbors = neighbors | 0b00010000;
						}
					}
					else {
						neighbors = (RENDER_BLOCKS_ON_WORLD_EDGE ? neighbors | 0b00010000 : neighbors | 0b00000000);
					}
					if (y != CHUNK_SIZE_Y - 1) {
						if (isBlockPrefabHasAlpha(x, y + 1, z)) {
							neighbors = neighbors | 0b00100000;
						}
					}
					else {
						neighbors = (RENDER_BLOCKS_ON_WORLD_EDGE ? neighbors | 0b00100000 : neighbors | 0b00000000);
					}

					if (neighbors & 0b00000001) {
						Block::Face& back = prefab->back;
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
					}
					if (neighbors & 0b00000010) {
						Block::Face& front = prefab->front;
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
					}
					if (neighbors & 0b00000100) {
						Block::Face& left = prefab->left;
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
					}
					if (neighbors & 0b00001000) {
						Block::Face& right = prefab->right;
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
					}
					if (neighbors & 0b00010000) {
						Block::Face& bottom = prefab->bottom;
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
					}
					if (neighbors & 0b00100000) {
						Block::Face& top = prefab->top;
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
		}

		if (vertices.size() == 0 || indices.size() == 0) {
			subChunk.VAO = 0;
			subChunk.IBO = 0;
			subChunk.VBO = 0;
			subChunk.vertices_length = 0;
			subChunk.indices_length = 0;
			return;
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
	void Chunk::createMeshes() {
		if (!Engine::isRunning()) {
			return;
		}
		if (updateMeshes == 0) {
			return;
		}
		*logger << bcppul::TRACE << "Updating chunk mesh X:" << position.x << "; z:" << position.y;
		for (unsigned int sub_chunk_i = 0; sub_chunk_i < SUB_CHUNKS_IN_CHUNK; ++sub_chunk_i)
		{
			if (updateMeshes & 1 << sub_chunk_i) {
				createMesh(sub_chunk_i);
			}
		}
		updateMeshes = 0;
	}
	void Chunk::deleteMeshes()
	{
		for (unsigned int i = 0; i < SUB_CHUNKS_IN_CHUNK; ++i)
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

	unsigned short Chunk::getBlock(int x, int y, int z)
	{
		if (y >= CHUNK_SIZE_Y || y < 0) {
			return 0;
		}
		return blocks[((y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + x * CHUNK_SIZE_Z) + z];
	}
	Block* Chunk::getBlockPrefab(int x, int y, int z)
	{
		if (y >= CHUNK_SIZE_Y || y < 0) {
			return BlocksManager::getBlock(0);
		}
		return BlocksManager::getBlock(getBlockID(x, y, z));
	}
	bool Chunk::isBlockPrefabHasAlpha(int x, int y, int z)
	{
		if (y >= CHUNK_SIZE_Y || y < 0) {
			return true;
		}
		Block* block = BlocksManager::getBlock(getBlockID(x, y, z));
		return block == nullptr || block->hasAlpha;
	}
	unsigned short Chunk::getBlockID(int x, int y, int z)
	{
		if (y >= CHUNK_SIZE_Y || y < 0) {
			return 0;
		}
		return getBlock(x, y, z) & 0x0FFF;
	}
	unsigned short Chunk::getBlockState(int x, int y, int z)
	{
		if (y >= CHUNK_SIZE_Y || y < 0) {
			return 0;
		}
		return getBlock(x, y, z) & 0xF000;
	}
	void Chunk::getBlock(int x, int y, int z, unsigned short& blockID, unsigned short& blockState)
	{
		if (y >= CHUNK_SIZE_Y || y < 0) {
			blockID = 0;
			blockState = 0;
			return;
		}
		unsigned short block = getBlock(x, y, z);
		blockID = block & 0x0FFF;
		blockState = block & 0xF000;
	}
	unsigned short Chunk::getBlock(glm::ivec3 position)
	{
		if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
			return 0;
		}
		return blocks[((position.y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + position.x * CHUNK_SIZE_Z) + position.z];
	}
	Block* Chunk::getBlockPrefab(glm::ivec3 position)
	{
		if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
			return BlocksManager::getBlock(0);
		}
		return BlocksManager::getBlock(getBlockID(position));
	}
	bool Chunk::isBlockPrefabHasAlpha(glm::ivec3 position)
	{
		if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
			return true;
		}
		Block* block = BlocksManager::getBlock(getBlockID(position));
		return block == nullptr || block->hasAlpha;
	}
	unsigned short Chunk::getBlockID(glm::ivec3 position)
	{
		if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
			return 0;
		}
		return getBlock(position) & 0x0FFF;
	}
	unsigned short Chunk::getBlockState(glm::ivec3 position)
	{
		if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
			return 0;
		}
		return getBlock(position) & 0xF000;
	}
	void Chunk::getBlock(glm::vec3 position, unsigned short& blockID, unsigned short& blockState)
	{
		if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
			blockID = 0;
			blockState = 0;
			return;
		}
		unsigned short block = getBlock(position);
		blockID = block & 0x0FFF;
		blockState = block & 0xF000;
	}
	unsigned short Chunk::getBlock(unsigned int i)
	{
		if (i >= CHUNK_VOLUME || i < 0) {
			return 0;
		}
		return blocks[i];
	}
	Block* Chunk::getBlockPrefab(unsigned int i)
	{
		if (i >= CHUNK_VOLUME || i < 0) {
			return BlocksManager::getBlock(0);
		}
		return BlocksManager::getBlock(getBlockID(i));
	}
	bool Chunk::isBlockPrefabHasAlpha(unsigned int i)
	{
		if (i >= CHUNK_VOLUME || i < 0) {
			return true;
		}
		Block* block = BlocksManager::getBlock(getBlockID(i));
		return block == nullptr || block->hasAlpha;
	}
	unsigned short Chunk::getBlockID(unsigned int i)
	{
		if (i >= CHUNK_VOLUME || i < 0) {
			return 0;
		}
		return getBlock(i) & 0x0FFF;
	}
	unsigned short Chunk::getBlockState(unsigned int i)
	{
		if (i >= CHUNK_VOLUME || i < 0) {
			return 0;
		}
		return getBlock(i) & 0xF000;
	}
	void Chunk::getBlock(unsigned int i, unsigned short& blockID, unsigned short& blockState)
	{
		if (i >= CHUNK_VOLUME || i < 0) {
			blockID = 0;
			blockState = 0;
			return;
		}
		unsigned short block = getBlock(i);
		blockID = block & 0x0FFF;
		blockState = block & 0xF000;
	}
	void Chunk::updateNeighbor(int x, int y, int z)
	{
		if (z == 0) {
			if (position.y != -world->getRenderDistance()) {
				world->getChunk(position.x, position.y - 1)->createMesh(y / 16);
			}
		} else if (z == CHUNK_SIZE_Z - 1) {
			if (position.y != -world->getRenderDistance()) {
				world->getChunk(position.x, position.y + 1)->createMesh(y / 16);
			}
		}
		if (x == 0) {
			if (position.x != -world->getRenderDistance()) {
				world->getChunk(position.x - 1, position.y)->createMesh(y / 16);
			}
		} else if (x == CHUNK_SIZE_X - 1) {
			if (position.x != -world->getRenderDistance()) {
				world->getChunk(position.x + 1, position.y)->createMesh(y / 16);
			}
		}
		int suby = y % SUB_CHUNK_SIZE_Y;
		if (suby == 0) {
			if (y != 0) {
				updateMeshes = updateMeshes | 1 << ((y / SUB_CHUNK_SIZE_Y) - 1);
			}
			if (y != CHUNK_SIZE_Y - 1) {
				updateMeshes = updateMeshes | 1 << ((y / SUB_CHUNK_SIZE_Y) + 1);
			}
		}
	}
	void Chunk::updateNeighbor(glm::ivec3 position)
	{
		updateNeighbor(position.x, position.y, position.z);
	}

	void Chunk::setBlock(int x, int y, int z, unsigned short block, unsigned short needUpdateMesh)
	{
		if (y >= CHUNK_SIZE_Y || y < 0) {
			return;
		}
		if (needUpdateMesh) {
			updateNeighbor(x, y, z);
		}
		blocks[((y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + x * CHUNK_SIZE_Z) + z] = block;
		if (needUpdateMesh != 0) {
			if (needUpdateMesh == 1) {
				updateMeshes = updateMeshes | (1 << (y / SUB_CHUNK_SIZE_Y));
			}
			else if (needUpdateMesh == 0b1111111111111111) {
				updateMeshes = 0b1111111111111111;
			}
		}
	}
	void Chunk::setBlock(glm::ivec3 position, unsigned short block, unsigned short needUpdateMesh)
	{
		if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
			return;
		}
		blocks[((position.y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + position.x * CHUNK_SIZE_Z) + position.z] = block;
		if (needUpdateMesh != 0) {
			if (needUpdateMesh == 1) {
				updateMeshes = updateMeshes | (1 << position.y / SUB_CHUNK_SIZE_Y);
			}
			else if (needUpdateMesh == 0b1111111111111111) {
				updateMeshes = 0b1111111111111111;
			}
		}
	}
	void Chunk::setBlock(unsigned int i, unsigned short block, unsigned short needUpdateMesh)
	{
		if (i >= CHUNK_VOLUME || i < 0) {
			return;
		}
		blocks[i] = block;
		if (needUpdateMesh != 0) {
			if (needUpdateMesh == 1) {
				updateMeshes = updateMeshes | (1 << (i / (CHUNK_SIZE_X * CHUNK_SIZE_Z * SUB_CHUNK_SIZE_Y)));
			}
			else if (needUpdateMesh == 0b1111111111111111) {
				updateMeshes = 0b1111111111111111;
			}
		}
	}
	void Chunk::setBlockAndState(int x, int y, int z, unsigned short blockID, unsigned short state, unsigned short needUpdateMesh)
	{
		if (y >= CHUNK_SIZE_Y || y < 0) {
			return;
		}
		blocks[((y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + x * CHUNK_SIZE_Z) + z] = blockID | (state << 12);
		if (needUpdateMesh != 0) {
			if (needUpdateMesh == 1) {
				updateMeshes = updateMeshes | (1 << y / SUB_CHUNK_SIZE_Y);
			}
			else if (needUpdateMesh == 0b1111111111111111) {
				updateMeshes = 0b1111111111111111;
			}
		}
	}
	void Chunk::setBlockAndState(glm::ivec3 position, unsigned short blockID, unsigned short state, unsigned short needUpdateMesh)
	{
		if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
			return;
		}
		blocks[((position.y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + position.x * CHUNK_SIZE_Z) + position.z] = blockID | (state << 12);
		if (needUpdateMesh != 0) {
			if (needUpdateMesh == 1) {
				updateMeshes = updateMeshes | (1 << (position.y / SUB_CHUNK_SIZE_Y));
			}
			else if (needUpdateMesh == 0b1111111111111111) {
				updateMeshes = 0b1111111111111111;
			}
		}
	}
	void Chunk::setBlockAndState(unsigned int i, unsigned short blockID, unsigned short state, unsigned short needUpdateMesh)
	{
		if (i >= CHUNK_VOLUME || i < 0) {
			return;
		}
		blocks[i] = blockID | (state << 12);
		if (needUpdateMesh != 0) {
			if (needUpdateMesh == 1) {
				updateMeshes = updateMeshes | (1 << (i / (CHUNK_SIZE_X * CHUNK_SIZE_Z * SUB_CHUNK_SIZE_Y)));
			}
			else if (needUpdateMesh == 0b1111111111111111){
				updateMeshes = 0b1111111111111111;
			}
		}
		
	}

	unsigned short Chunk::getUpdatableMeshes()
	{
		return updateMeshes;
	}

	void Chunk::setNeedUpdateFullChunk()
	{
		updateMeshes = 0b1111111111111111;
	}

	void Chunk::setNeedUpdate(unsigned short meshes)
	{
		updateMeshes = meshes;
	}

	void Chunk::finalization() {
		delete[] blocks;
		deleteMeshes();
	}
}