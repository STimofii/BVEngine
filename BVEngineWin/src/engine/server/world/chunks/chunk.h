#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <bcppul/logging.h>
#include "../../blocks/blocks_manager.h"
#include "../../blocks/block.h"

namespace bulka {
#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16
#define SUB_CHUNK_SIZE_Y 16
#define SUB_CHUNKS_IN_CHUNK (CHUNK_SIZE_Y / SUB_CHUNK_SIZE_Y)
#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)
#define SUB_CHUNK_VOLUME (CHUNK_SIZE_X * SUB_CHUNK_SIZE_Y * CHUNK_SIZE_Z)
#define RENDER_BLOCKS_ON_WORLD_EDGE true
	class World;
	class Chunk{
	private:
		static bcppul::Logger* logger;
		struct SubChunk {
			unsigned int VAO;
			unsigned int VBO;
			unsigned int IBO;
			unsigned int vertices_length;
			unsigned int indices_length;
		};
		World* world;
		glm::ivec2 position;
		glm::ivec2 blockStartPosition;
		bool needUpdate = true;
		unsigned short* blocks = nullptr;
		SubChunk sub_chunks[SUB_CHUNKS_IN_CHUNK]{};
	protected:
	public:
		Chunk(World* world, glm::ivec2 position);
		Chunk(const Chunk& other) = delete;
		Chunk& operator=(const Chunk& other) = delete;
		~Chunk();
		void generate();
		void createMeshes();
		void deleteMeshes();
		void update();
		void render();
		void finalization();

		inline unsigned short getBlock(int x, int y, int z)
		{
			if (y >= CHUNK_SIZE_Y || y < 0) {
				return 0;
			}
			return blocks[((y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + x * CHUNK_SIZE_Z) + z];
		}
		inline Block* getBlockPrefab(int x, int y, int z)
		{
			if (y >= CHUNK_SIZE_Y || y < 0) {
				return BlocksManager::getBlock(0);
			}
			return BlocksManager::getBlock(getBlockID(x, y, z));
		}
		inline bool isBlockPrefabHasAlpha(int x, int y, int z)
		{
			if (y >= CHUNK_SIZE_Y || y < 0) {
				return true;
			}
			Block* block = BlocksManager::getBlock(getBlockID(x, y, z));
			return block == nullptr || block->hasAlpha;
		}
		inline unsigned short getBlockID(int x, int y, int z)
		{
			if (y >= CHUNK_SIZE_Y || y < 0) {
				return 0;
			}
			return getBlock(x, y, z) & 0x0FFF;
		}
		inline unsigned short getBlockState(int x, int y, int z)
		{
			if (y >= CHUNK_SIZE_Y || y < 0) {
				return 0;
			}
			return getBlock(x, y, z) & 0xF000;
		}
		inline void getBlock(int x, int y, int z, unsigned short& blockID, unsigned short& blockState)
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
		inline unsigned short getBlock(glm::ivec3 position)
		{
			if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
				return 0;
			}
			return blocks[((position.y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + position.x * CHUNK_SIZE_Z) + position.z];
		}
		inline Block* getBlockPrefab(glm::ivec3 position)
		{
			if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
				return BlocksManager::getBlock(0);
			}
			return BlocksManager::getBlock(getBlockID(position));
		}
		inline bool isBlockPrefabHasAlpha(glm::ivec3 position)
		{
			if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
				return true;
			}
			Block* block = BlocksManager::getBlock(getBlockID(position));
			return block == nullptr || block->hasAlpha;
		}
		inline unsigned short getBlockID(glm::ivec3 position)
		{
			if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
				return 0;
			}
			return getBlock(position) & 0x0FFF;
		}
		inline unsigned short getBlockState(glm::ivec3 position)
		{
			if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
				return 0;
			}
			return getBlock(position) & 0xF000;
		}
		inline void getBlock(glm::vec3 position, unsigned short& blockID, unsigned short& blockState)
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
		inline unsigned short getBlock(unsigned int i)
		{
			if (i >= CHUNK_VOLUME || i < 0) {
				return 0;
			}
			return blocks[i];
		}
		inline Block* getBlockPrefab(unsigned int i)
		{
			if (i >= CHUNK_VOLUME || i < 0) {
				return BlocksManager::getBlock(0);
			}
			return BlocksManager::getBlock(getBlockID(i));
		}
		inline bool isBlockPrefabHasAlpha(unsigned int i)
		{
			if (i >= CHUNK_VOLUME || i < 0) {
				return true;
			}
			Block* block = BlocksManager::getBlock(getBlockID(i));
			return block == nullptr || block->hasAlpha;
		}
		inline unsigned short getBlockID(unsigned int i)
		{
			if (i >= CHUNK_VOLUME || i < 0) {
				return 0;
			}
			return getBlock(i) & 0x0FFF;
		}
		inline unsigned short getBlockState(unsigned int i)
		{
			if (i >= CHUNK_VOLUME || i < 0) {
				return 0;
			}
			return getBlock(i) & 0xF000;
		}
		inline void getBlock(unsigned int i, unsigned short& blockID, unsigned short& blockState)
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
		inline void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned short block, bool needUpdateMesh)
		{
			if (y >= CHUNK_SIZE_Y || y < 0) {
				return;
			}
			blocks[((y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + x * CHUNK_SIZE_Z) + z] = block;
			needUpdate = needUpdateMesh;
		}
		inline void setBlock(glm::ivec3 position, unsigned short block, bool needUpdateMesh)
		{
			if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
				return;
			}
			blocks[((position.y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + position.x * CHUNK_SIZE_Z) + position.z] = block;
			needUpdate = needUpdateMesh;
		}
		inline void setBlock(unsigned int i, unsigned short block, bool needUpdateMesh)
		{
			if (i >= CHUNK_VOLUME || i < 0) {
				return;
			}
			blocks[i] = block;
			needUpdate = needUpdateMesh;
		}
		inline void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned short blockID, unsigned short state, bool needUpdateMesh)
		{
			if (y >= CHUNK_SIZE_Y || y < 0) {
				return;
			}
			blocks[((y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + x * CHUNK_SIZE_Z) + z] = blockID | (state << 12);
			needUpdate = needUpdateMesh;
		}
		inline void setBlock(glm::ivec3 position, unsigned short blockID, unsigned short state, bool needUpdateMesh)
		{
			if (position.y >= CHUNK_SIZE_Y || position.y < 0) {
				return;
			}
			blocks[((position.y * CHUNK_SIZE_X * CHUNK_SIZE_Z) + position.x * CHUNK_SIZE_Z) + position.z] = blockID | (state << 12);
			needUpdate = needUpdateMesh;
		}
		inline void setBlock(unsigned int i, unsigned short blockID, unsigned short state, bool needUpdateMesh)
		{
			if (i >= CHUNK_VOLUME || i < 0) {
				return;
			}
			blocks[i] = blockID | (state << 12);
			needUpdate = needUpdateMesh;
		}
		bool isNeedUpdate();
		void setNeedUpdate(bool val);
	};

}