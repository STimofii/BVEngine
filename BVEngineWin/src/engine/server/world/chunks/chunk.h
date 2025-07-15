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
	};

}