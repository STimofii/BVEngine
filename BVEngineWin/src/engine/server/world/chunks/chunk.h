#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <bcppul/logging.h>

namespace bulka {
#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16
#define SUB_CHUNK_SIZE_Y 16
#define SUB_CHUNKS_IN_CHUNK (CHUNK_SIZE_Y / SUB_CHUNK_SIZE_Y)
#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)
#define SUB_CHUNK_VOLUME (CHUNK_SIZE_X * SUB_CHUNK_SIZE_Y * CHUNK_SIZE_Z)
#define RENDER_BLOCKS_ON_WORLD_EDGE false
	class World;
	class Block;
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
		World* world = nullptr;
		glm::ivec2 position;
		glm::ivec2 globalPosition;
		glm::ivec2 blockStartPosition;
		glm::ivec2 blockStartGlobalPosition;
		unsigned short updateMeshes = 0b0;
		unsigned short* blocks = nullptr;
		SubChunk sub_chunks[SUB_CHUNKS_IN_CHUNK]{};
		bool moved = false;
		bool generating= false;
		bool generated = false;
		bool initialized = false;
		bool forDelete = false;
	protected:
	public:
		Chunk(World* world, glm::ivec2 position, glm::ivec2 globalPosition);
		Chunk(const Chunk& other) = delete;
		Chunk& operator=(const Chunk& other) = delete;
		~Chunk();
		void generate();
		int mandelbrot(float x, float y);
		bool createMesh(unsigned int sub_chunk_i);
		bool createMeshes();
		void deleteMeshes();
		void update();
		void render();
		void finalization();

		glm::ivec2 getPosition();
		glm::ivec2 getBlockStartPosition();
		glm::ivec2 getGlobalPosition();
		glm::ivec2 getBlockStartGlobalPosition();
		void setPosition(int x, int z);
		void setGlobalPosition(int x, int z);
		void setPositionAndGlobalPosition(int x, int z);
		void addPosition(int x, int z);
		void addGlobalPosition(int x, int z);
		void addPositionAndGlobalPosition(int x, int z);
		void setPosition(glm::ivec2 pos);
		void setGlobalPosition(glm::ivec2 pos);
		void setPositionAndGlobalPosition(glm::ivec2 pos);
		void addPosition(glm::ivec2 pos);
		void addGlobalPosition(glm::ivec2 pos);
		void addPositionAndGlobalPosition(glm::ivec2 pos);

		unsigned short getBlock(int x, int y, int z);
		Block* getBlockPrefab(int x, int y, int z);
		bool isBlockPrefabHasAlpha(int x, int y, int z);
		unsigned short getBlockID(int x, int y, int z);
		unsigned short getBlockState(int x, int y, int z);
		void getBlock(int x, int y, int z, unsigned short& blockID, unsigned short& blockState);
		unsigned short getBlock(glm::ivec3 position);
		Block* getBlockPrefab(glm::ivec3 position);
		bool isBlockPrefabHasAlpha(glm::ivec3 position);
		unsigned short getBlockID(glm::ivec3 position);
		unsigned short getBlockState(glm::ivec3 position);
		void getBlock(glm::vec3 position, unsigned short& blockID, unsigned short& blockState);
		unsigned short getBlock(unsigned int i);
		Block* getBlockPrefab(unsigned int i);
		bool isBlockPrefabHasAlpha(unsigned int i);
		unsigned short getBlockID(unsigned int i);
		unsigned short getBlockState(unsigned int i);
		void getBlock(unsigned int i, unsigned short& blockID, unsigned short& blockState);

		void updateNeighbor(int x, int y, int z);
		void updateNeighbor(glm::ivec3 position);
		void setBlock(int x, int y, int z, unsigned short block, unsigned short needUpdateMesh = 0);
		void setBlock(glm::ivec3 position, unsigned short block, unsigned short needUpdateMesh = 0);
		void setBlock(unsigned int i, unsigned short block, unsigned short needUpdateMesh = 0);
		void setBlockAndState(int x, int y, int z, unsigned short blockID, unsigned short state, unsigned short needUpdateMesh = 0);
		void setBlockAndState(glm::ivec3 position, unsigned short blockID, unsigned short state, unsigned short needUpdateMesh = 0);
		void setBlockAndState(unsigned int i, unsigned short blockID, unsigned short state, unsigned short needUpdateMesh = 0);

		unsigned short getUpdatableMeshes();
		void setNeedUpdateFullChunk();
		void setNeedUpdate(unsigned short meshes);
		bool isMoved();
		bool isGenerated();
		bool isGenerating();
		void setMoved(bool val);

		bool isForDelete();
		void setForDelete(bool val);
	};

}