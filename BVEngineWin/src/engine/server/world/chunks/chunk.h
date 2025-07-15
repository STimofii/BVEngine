#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <bcppul/logging.h>

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16
#define SUB_CHUNK_SIZE_Y 16
#define SUB_CHUNKS_IN_CHUNK (CHUNK_SIZE_Y / SUB_CHUNK_SIZE_Y)
#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)
#define SUB_CHUNK_VOLUME (CHUNK_SIZE_X * SUB_CHUNK_SIZE_Y * CHUNK_SIZE_Z)
namespace bulka {
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
		glm::ivec2 position;
		glm::ivec2 blockStartPosition;
		bool needUpdate = true;
		unsigned short* blocks = nullptr;
		SubChunk sub_chunks[SUB_CHUNKS_IN_CHUNK]{};
	protected:
	public:
		Chunk(glm::ivec2 position);
		Chunk(const Chunk& other) = delete;
		Chunk& operator=(const Chunk& other) = delete;
		~Chunk();
		void generate();
		void createMeshes();
		void deleteMeshes();
		void update();
		void render();
		void finalization();

		unsigned short getBlock(unsigned int x, unsigned int y, unsigned int z);
		Block* getBlockPrefab(unsigned int x, unsigned int y, unsigned int z);
		unsigned short getBlockID(unsigned int x, unsigned int y, unsigned int z);
		unsigned short getBlockState(unsigned int x, unsigned int y, unsigned int z);
		void getBlock(unsigned int x, unsigned int y, unsigned int z, unsigned short& blockID, unsigned short& blockState);
		unsigned short getBlock(glm::ivec3 position);
		Block* getBlockPrefab(glm::ivec3 position);
		unsigned short getBlockID(glm::ivec3 position);
		unsigned short getBlockState(glm::ivec3 position);
		void getBlock(glm::vec3 position, unsigned short& blockID, unsigned short& blockState);
		unsigned short getBlock(unsigned int i);
		Block* getBlockPrefab(unsigned int i);
		unsigned short getBlockID(unsigned int i);
		unsigned short getBlockState(unsigned int i);
		void getBlock(unsigned int i, unsigned short& blockID, unsigned short& blockState);

		void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned short block, bool needUpdateMesh = false);
		void setBlock(glm::ivec3 position, unsigned short block, bool needUpdateMesh = false);
		void setBlock(unsigned int i, unsigned short block, bool needUpdateMesh = false);
		void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned short blockID, unsigned short state, bool needUpdateMesh = false);
		void setBlock(glm::ivec3 position, unsigned short blockID, unsigned short state, bool needUpdateMesh = false);
		void setBlock(unsigned int i, unsigned short blockID, unsigned short state, bool needUpdateMesh = false);
		bool isNeedUpdate();
		void setNeedUpdate(bool val);
	};

}