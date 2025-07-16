#include "world.h"

#include "chunks/chunk.h"
#include "../../graphics/texture_manager.h"
#include "../../graphics/shader_manager.h"
#include "../../settings.h"
#include "../../engine.h"
#include "../../hero.h"
#include <iostream>
#include <algorithm>
#include <thread>



namespace bulka {
	bcppul::Logger* World::logger = bcppul::getLogger("World");
	World::World()
	{
	}
	World::~World()
	{
		if(chunks != nullptr){
			delete[] chunks;
			chunks = nullptr;
		}
	}

	void World::load() {
		setRenderDistance(Settings::RENDER_DISTANCE);
		chunks = new Chunk*[chunks_world_count];
		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				unsigned int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				chunks[i] = new Chunk(this, glm::ivec2(x, z), glm::ivec2(x, z));
				chunksForGenerateMutex.lock();
				chunksForGenerate.push_back(chunks[i]);
				chunksForGenerateMutex.unlock();
			}
		}
		generate();

	}
	void World::generate() {

	}
	void World::reload() {

	}

	void World::recreateAllMeshes()
	{
		chunksForCreateMeshMutex.lock();
		for (unsigned int i = 0; i < chunks_world_count; ++i) {
			chunks[i]->setNeedUpdateFullChunk();
			chunksForCreateMesh.push_back(chunks[i]);
		}
		chunksForCreateMeshMutex.unlock();
	}

	void World::update() {
		unsigned int created_count = 0;
		chunksForCreateMeshMutex.lock();
		auto it = chunksForCreateMesh.begin();
		while (it != chunksForCreateMesh.end()) {
			if (Settings::RENDER_CHUNKS_BY_CYCLE_COUNT == 0 || created_count >= Settings::RENDER_CHUNKS_BY_CYCLE_COUNT) {
				break;
			}
			Chunk* chunk = *it;
			created_count += chunk->createMeshes();
			it = chunksForCreateMesh.erase(it);
		}
		chunksForCreateMeshMutex.unlock();

		chunksForDestroyMutex.lock();
		auto new_end = std::remove_if(chunksForDestroy.begin(), chunksForDestroy.end(), [](Chunk* chunk) {
			if (chunk->isGenerated() && !chunk->isGenerating()) {
				chunk->finalization();
				delete chunk;
				return true;
			}
			return false;
			});
		chunksForDestroy.erase(new_end, chunksForDestroy.end());
		chunksForDestroyMutex.unlock();
	}
	void World::serverUpdate()
	{
		chunksForGenerateMutex.lock();
		auto it = chunksForGenerate.begin();
		while (it != chunksForGenerate.end()) {
			Chunk* chunk = *it;
			if (chunk != nullptr && !chunk->isGenerated() && !chunk->isGenerating()) {
				if (std::thread::hardware_concurrency() <= 2) {
					chunk->generate();
					chunksForCreateMeshMutex.lock();
					chunksForCreateMesh.push_back(chunk);
					chunksForCreateMeshMutex.unlock();
				}
				else {
					if (generateThreadsCount < std::thread::hardware_concurrency() - 2) {
						std::thread th([chunk, this]() {
							if (chunk != nullptr) {
								chunk->generate();
								chunksForCreateMeshMutex.lock();
								chunksForCreateMesh.push_back(chunk);
								chunksForCreateMeshMutex.unlock();
							}
							});
						th.detach();
						++generateThreadsCount;
					}
					else {
						break;
					}
				}
			}
			//std::cerr << (void*)(*it) << "/" << (void*)(*chunksForGenerate.end()) << std::endl;
			it = chunksForGenerate.erase(it);
		}
		chunksForGenerateMutex.unlock();
	}
	void World::render() {
		ShaderManager::chunkShader.bind();
		TextureManager::bindTexture("res/textures/blocks.png");
		for (int i = 0; i < chunks_world_count; ++i) {
			chunks[i]->render();
		}
		TextureManager::unbindTexture();
		ShaderManager::chunkShader.unbind();
	}
	void World::save() {

	}
	int World::getRenderDistance()
	{
		return render_distance;
	}
	int World::getChunksWorldWidth()
	{
		return chunks_world_width;
	}
	int World::getChunksWorldCount()
	{
		return chunks_world_count;
	}
	void World::setRenderDistance(int val)
	{
		if (this == nullptr) {
			return;
		}
		int new_render_distance = val;
		int new_chunks_world_width = new_render_distance * 2 + 1;
		int new_chunks_world_count = new_chunks_world_width * new_chunks_world_width;
		if (chunks != nullptr) {
			glm::ivec2 heroChunkPos = glm::ivec2(
				std::floor(Engine::getHero().getChunksPosition().x),
				std::floor(Engine::getHero().getChunksPosition().z)
			);
			Chunk** tempChunks = new Chunk* [new_chunks_world_count];
			for (int x = -new_render_distance; x <= new_render_distance; ++x) {
				for (int z = -new_render_distance; z <= new_render_distance; ++z) {
					int i = ((x + new_render_distance) * new_chunks_world_width) + z + new_render_distance;
					if (x >= -render_distance && x <= render_distance && z >= -render_distance && z <= render_distance) {
						int old_i = ((x + render_distance) * chunks_world_width) + z + render_distance;
						tempChunks[i] = chunks[old_i];
						tempChunks[i]->setMoved(true);
					}
					else {
						tempChunks[i] = new Chunk(this, glm::ivec2(x, z), heroChunkPos + glm::ivec2(x, z));
						chunksForGenerateMutex.lock();
						chunksForGenerate.push_back(tempChunks[i]);
						chunksForGenerateMutex.unlock();
					}
				}
			}
			for (unsigned int i = 0; i < chunks_world_count; ++i) {
				if(chunks[i]->isMoved()){
					chunks[i]->setMoved(false);
				}
				else {
					chunksForDestroyMutex.lock();
					chunksForDestroy.push_back(chunks[i]);
					chunksForDestroyMutex.unlock();
				}
			}
			delete[] chunks;
			chunks = tempChunks;
		}
		render_distance = new_render_distance;
		chunks_world_width = new_chunks_world_width;
		chunks_world_count = new_chunks_world_count;
	}
	void World::moveChunks(int offsetX, int offsetZ){
		if (offsetX == 0 && offsetZ == 0) {
			return;
		}
		//*logger << bcppul::TRACE << "Moving chunks with offset x: " << offsetX << "; z: " << offsetZ;
		//offsetX = -offsetX;
		//offsetZ = -offsetZ;
		Chunk** tempChunks = new Chunk* [chunks_world_count];
		for (unsigned int i = 0; i < chunks_world_count; ++i) {
			tempChunks[i] = nullptr;
		}

		glm::ivec2 heroChunkPos = glm::ivec2(
			std::floor(Engine::getHero().getChunksPosition().x),
			std::floor(Engine::getHero().getChunksPosition().z)
		);
		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				int newX = x - offsetX;
				int newZ = z - offsetZ;
				int new_i = ((newX + render_distance) * chunks_world_width) + newZ + render_distance;
				if (newX >= -render_distance && newX <= render_distance &&
					newZ >= -render_distance && newZ <= render_distance) {
					tempChunks[new_i] = chunks[i];
					tempChunks[new_i]->addPosition(-offsetX, -offsetZ);
				}
				else {
					chunksForDestroyMutex.lock();
					chunksForDestroy.push_back(chunks[i]);
					chunksForDestroyMutex.unlock();
				}
			}
		}

		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				if (tempChunks[i] == nullptr) {
					tempChunks[i] = new Chunk(this, glm::ivec2(x, z), heroChunkPos + glm::ivec2(x, z));
					chunksForGenerateMutex.lock();
					chunksForGenerate.push_back(tempChunks[i]);
					chunksForGenerateMutex.unlock();
				}
			}
		}
		delete[] chunks;
		chunks = tempChunks;
	}
	void World::decreaseGenerateThreadsCount()
	{
		multiTChunkGeneratingMutex.lock();
		if(generateThreadsCount != 0){
			--generateThreadsCount;
		}
		multiTChunkGeneratingMutex.unlock();
	}
}
