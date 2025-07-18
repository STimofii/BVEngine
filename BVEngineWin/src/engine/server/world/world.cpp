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
		auto updateMeshes = [this, &created_count](Chunk* chunk) {
			if (chunk == nullptr || chunk->isForDeleting()) {
				return true;
			}
			if (Settings::RENDER_CHUNKS_BY_CYCLE_COUNT == 0 || created_count >= Settings::RENDER_CHUNKS_BY_CYCLE_COUNT) {
				return false;
			}
			if (!chunk->isForDeleting()) {
				created_count += chunk->createMeshes();
			}
			return true;
			};
		chunksForCreateMeshMutex.lock();
		auto new_end = std::remove_if(chunksForCreateMesh.begin(), chunksForCreateMesh.end(), updateMeshes);
		chunksForCreateMesh.erase(new_end, chunksForCreateMesh.end());
		chunksForCreateMeshMutex.unlock();

		chunksForDestroyMutex.lock();
		chunksForDestroyDeletingMutex.lock();
		new_end = std::remove_if(chunksForDestroy.begin(), chunksForDestroy.end(), [this](Chunk* chunk) {
			if (chunk == nullptr) {
				return true;
			}
			if (!chunk->isGenerating()) {
				removeChunkFromChunksForGenerate(chunk);
				removeChunkFromChunksForCreateMesh(chunk);
				chunk->finalization();
				delete chunk;
				return true;
			}
			return false;
			});
		chunksForDestroy.erase(new_end, chunksForDestroy.end());
		chunksForDestroyDeletingMutex.unlock();
		chunksForDestroyMutex.unlock();
	}
	void World::serverUpdate()
	{
		auto generateChunk = [this](Chunk* chunk) {
			if (chunk == nullptr || chunk->isForDeleting()) {
				--generateThreadsCount;
				return;
			}
			chunk->setGenerating(true);
			chunk->generate();
			--generateThreadsCount;
			chunk->setGenerating(false);
			addChunkForCreateMesh(chunk);
			};

		std::vector<Chunk*> chunksToProcess;

		chunksForDestroyDeletingMutex.lock();
		chunksForGenerateMutex.lock();
		chunksToProcess.swap(chunksForGenerate);
		chunksForGenerateMutex.unlock();

		for (Chunk* chunk : chunksToProcess) {
			if (chunk != nullptr && !chunk->isForDeleting() && !chunk->isGenerated() && !chunk->isGenerating()) {
				if (std::thread::hardware_concurrency() <= 2) {
					generateChunk(chunk);
				}
				else {
					if (generateThreadsCount < std::thread::hardware_concurrency() - 2) {
						++generateThreadsCount;
						std::thread th(generateChunk, chunk);
						th.detach();
					}
					else {
						chunksForGenerateMutex.lock();
						chunksForGenerate.push_back(chunk);
						chunksForGenerateMutex.unlock();
					}
				}
			}
			else {

			}
		}
		chunksForDestroyDeletingMutex.unlock();
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
	void World::addChunkForGenerate(Chunk* chunk)
	{
		chunksForGenerateMutex.lock();
		chunksForGenerate.push_back(chunk);
		chunksForGenerateMutex.unlock();
	}
	void World::addChunkForCreateMesh(Chunk* chunk)
	{
		chunksForCreateMeshMutex.lock();
		chunksForCreateMesh.push_back(chunk);
		chunksForCreateMeshMutex.unlock();
	}
	void World::addChunkForDestroy(Chunk* chunk)
	{
		chunk->setForDeleting(true);
		chunksForDestroyMutex.lock();
		chunksForDestroy.push_back(chunk);
		chunksForDestroyMutex.unlock();
	}
	std::vector<Chunk*>& World::getChunksForGenerate()
	{
		return chunksForGenerate;
	}
	std::vector<Chunk*>& World::getChunksForCreateMesh()
	{
		return chunksForCreateMesh;
	}
	std::vector<Chunk*>& World::getChunksForDestroy()
	{
		return chunksForDestroy;
	}
	void World::removeChunkFromChunksForGenerate(Chunk* chunk)
	{
		chunksForGenerateMutex.lock();
		chunksForGenerate.erase(std::remove(chunksForGenerate.begin(), chunksForGenerate.end(), chunk), chunksForGenerate.end());
		chunksForGenerateMutex.unlock();
	}
	void World::removeChunkFromChunksForCreateMesh(Chunk* chunk)
	{
		chunksForCreateMeshMutex.lock();
		chunksForCreateMesh.erase(std::remove(chunksForCreateMesh.begin(), chunksForCreateMesh.end(), chunk), chunksForCreateMesh.end());
		chunksForCreateMeshMutex.unlock();
	}
	void World::removeChunkFromChunksForDestroy(Chunk* chunk)
	{
		chunksForDestroyMutex.lock();
		chunksForDestroy.erase(std::remove(chunksForDestroy.begin(), chunksForDestroy.end(), chunk), chunksForDestroy.end());
		chunksForDestroyMutex.unlock();
	}
	unsigned int World::getChunksForGenerateSize()
	{
		return chunksForGenerate.size();
	}
	unsigned int World::getChunksForCreateMeshSize()
	{
		return chunksForCreateMesh.size();
	}
	unsigned int World::getChunksForDestroySize()
	{
		return chunksForDestroy.size();
	}
	int World::getLoadedChunksCount()
	{
		return loadedChunksCount.load();
	}
	void World::increaseLoadedChunksCount()
	{
		++loadedChunksCount;
	}
	void World::decreaseLoadedChunksCount()
	{
		--loadedChunksCount;
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
						addChunkForGenerate(tempChunks[i]);
					}
				}
			}
			for (unsigned int i = 0; i < chunks_world_count; ++i) {
				if(chunks[i]->isMoved()){
					chunks[i]->setMoved(false);
				}
				else {
					addChunkForDestroy(chunks[i]);
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
					addChunkForDestroy(chunks[i]);
				}
			}
		}

		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				if (tempChunks[i] == nullptr) {
					tempChunks[i] = new Chunk(this, glm::ivec2(x, z), heroChunkPos + glm::ivec2(x, z));
					addChunkForGenerate(tempChunks[i]);
				}
			}
		}
		delete[] chunks;
		chunks = tempChunks;
	}
	void World::decreaseGenerateThreadsCount()
	{
		if(generateThreadsCount != 0){
			--generateThreadsCount;
		}
	}
	int World::getGenerateThreadsCount()
	{
		return generateThreadsCount;
	}
}
