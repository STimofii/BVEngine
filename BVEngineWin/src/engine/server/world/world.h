#pragma once

#include <vector>
#include <cmath>
#include <bcppul/logging.h>

#include "chunks/chunk.h"


namespace bulka {
	class World{
	private:
		static bcppul::Logger* logger;
		Chunk** chunks = nullptr;
		int render_distance = 2;
		int chunks_world_width = render_distance * 2 + 1;
		int chunks_world_count = chunks_world_width * chunks_world_width;
	protected:
	public:
		World();
		~World();
		void load();
		void reload();
		void generate();
		void update();
		void render();
		void save();

		int getRenderDistance();
		int getChunksWorldWidth();
		int getChunksWorldCount();
		void setRenderDistance(int val);


		inline Chunk** getChunks() {
			return chunks;
		}
		inline Chunk* getChunk(int x, int z) {
			if (x > render_distance || x < -render_distance || z > render_distance || z < -render_distance) {
				return nullptr;
			}
			return chunks[((x + render_distance) * chunks_world_width) + z + render_distance];
		}
		inline Chunk* getChunk(int i) {
			if (i > chunks_world_count) {
				return nullptr;
			}
			return chunks[i];
		}
		inline Chunk* getChunk(glm::ivec2 position) {
			if (position.x > render_distance || position.x < -render_distance || position.y > render_distance || position.y < -render_distance) {
				return nullptr;
			}
			return chunks[((position.x + render_distance) * chunks_world_width) + position.y + render_distance];
		}
		inline Chunk* getChunkInBlockCoords(int x, int z) {
			int chunkX = x / CHUNK_SIZE_X;
			int chunkZ = z / CHUNK_SIZE_Z;
			if (chunkX > render_distance || chunkX < -render_distance || chunkZ > render_distance || chunkZ < -render_distance) {
				return nullptr;
			}
			return chunks[((chunkX + render_distance) * chunks_world_width) + chunkZ + render_distance];
		}
		inline Chunk* getChunkInBlockCoords(glm::ivec2 position) {
			int chunkX = position.x / CHUNK_SIZE_X;
			int chunkZ = position.y / CHUNK_SIZE_Z;
			if (position.x / CHUNK_SIZE_X > render_distance || position.y / CHUNK_SIZE_Z > render_distance) {
				return nullptr;
			}
			if (chunkX > render_distance || chunkX < -render_distance || chunkZ > render_distance || chunkZ < -render_distance) {
				return nullptr;
			}
			return chunks[((chunkX + render_distance) * chunks_world_width) + chunkZ + render_distance];
		}

		inline unsigned short getBlock(unsigned int x, unsigned int y, unsigned int z)
		{
			unsigned int bx = x % CHUNK_SIZE_X;
			unsigned int bz = z % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(x, z)->getBlock(bx, y, bz);
		}
		inline Block* getBlockPrefab(unsigned int x, unsigned int y, unsigned int z)
		{
			unsigned int bx = x % CHUNK_SIZE_X;
			unsigned int bz = z % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(x, z)->getBlockPrefab(bx, y, bz);
		}
		inline unsigned short getBlockID(unsigned int x, unsigned int y, unsigned int z)
		{
			unsigned int bx = x % CHUNK_SIZE_X;
			unsigned int bz = z % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(x, z)->getBlockID(bx, y, bz);
		}
		inline unsigned short getBlockState(unsigned int x, unsigned int y, unsigned int z)
		{
			unsigned int bx = x % CHUNK_SIZE_X;
			unsigned int bz = z % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(x, z)->getBlockState(bx, y, bz);
		}
		inline void getBlock(unsigned int x, unsigned int y, unsigned int z, unsigned short& blockID, unsigned short& blockState)
		{
			unsigned int bx = x % CHUNK_SIZE_X;
			unsigned int bz = z % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(x, z)->getBlock(bx, y, bz, blockID, blockState);
		}
		inline unsigned short getBlock(glm::ivec3 position)
		{
			unsigned int bx = position.x % CHUNK_SIZE_X;
			unsigned int bz = position.y % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(position)->getBlock(bx, position.y, bz);
		}
		inline Block* getBlockPrefab(glm::ivec3 position)
		{
			unsigned int bx = position.x % CHUNK_SIZE_X;
			unsigned int bz = position.y % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(position)->getBlockPrefab(bx, position.y, bz);
		}
		inline unsigned short getBlockID(glm::ivec3 position)
		{
			unsigned int bx = position.x % CHUNK_SIZE_X;
			unsigned int bz = position.y % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(position)->getBlockID(bx, position.y, bz);
		}

		inline unsigned short getBlockState(glm::ivec3 position)
		{
			unsigned int bx = position.x % CHUNK_SIZE_X;
			unsigned int bz = position.y % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(position)->getBlockState(position.x % 16, position.y, position.z % 16);
		}
		inline void getBlock(glm::ivec3 position, unsigned short& blockID, unsigned short& blockState)
		{
			unsigned int bx = position.x % CHUNK_SIZE_X;
			unsigned int bz = position.y % CHUNK_SIZE_Z;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			return getChunkInBlockCoords(position)->getBlock(bx, position.y, bz, blockID, blockState);
		}

		inline void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned short block, unsigned short needUpdateMesh = 1)
		{
			unsigned int bx = x % 16;
			unsigned int bz = z % 16;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			getChunkInBlockCoords(x, z)->setBlock(bx, y, bz, block, needUpdateMesh);
		}
		inline void setBlock(glm::ivec3 position, unsigned short block, unsigned short needUpdateMesh = 1)
		{
			unsigned int bx = position.x % 16;
			unsigned int bz = position.z % 16;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			getChunkInBlockCoords(position.x, position.z)->setBlock(bx, position.y, bz, block, needUpdateMesh);
		}
		inline void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned short blockID, unsigned short state, unsigned short needUpdateMesh = 1)
		{
			unsigned int bx = x % 16;
			unsigned int bz = z % 16;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			getChunkInBlockCoords(x, z)->setBlockAndState(bx, y, bz, blockID, state, needUpdateMesh);
		}
		inline void setBlock(glm::ivec3 position, unsigned short blockID, unsigned short state, unsigned char needUpdateMesh = 1)
		{
			unsigned int bx = position.x % 16;
			unsigned int bz = position.z % 16;
			if (bx < 0) {
				bx += CHUNK_SIZE_X - 1;
			}
			if (bz < 0) {
				bz += CHUNK_SIZE_Z - 1;
			}
			getChunkInBlockCoords(position.x, position.z)->setBlockAndState(bx, position.y, bz, blockID, state, needUpdateMesh);
		}
	};

}

