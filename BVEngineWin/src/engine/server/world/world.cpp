#include "world.h"

#include "chunks/chunk.h"
#include "../../graphics/texture_manager.h"
#include "../../graphics/shader_manager.h"
#include "../../settings.h"
#include "../../engine.h"
#include "../../hero.h"
#include <iostream>
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
		chunks = new std::shared_ptr<Chunk>[chunks_world_count];
		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				unsigned int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				chunks[i] = std::make_shared<Chunk>(this, glm::ivec2(x, z), glm::ivec2(x, z));
			}
		}
		generate();

	}
	void World::generate() {

	}
	void World::reload() {
		unsigned int rendered_count = 0;
		for (int i = 0; i < chunks_world_count; ++i) {
			if (rendered_count != 0 && rendered_count == Settings::RENDER_CHUNKS_BY_CYCLE_COUNT) {
				return;
			}
			rendered_count += chunks[i]->createMeshes();
		}
	}
	void World::update() {
		//for (int i = 0; i < chunks_world_count; ++i) {
		//	if (chunks[i]->isForDelete() && chunks[i]->isGenerated()) {
		//		chunks[i]->finalization();
		//		delete chunks[i];
		//		chunks[i] = nullptr;
		//	}
		//}
	}
	void World::serverUpdate()
	{
		for (int i = 0; i < chunks_world_count; ++i) {
			if (chunks[i] != nullptr && !chunks[i]->isGenerated() && !chunks[i]->isGenerating()) {
				if (std::thread::hardware_concurrency() <= 2) {
					chunks[i]->generate();
				} else {
					if (generateThreadsCount < std::thread::hardware_concurrency() - 2) {
						std::shared_ptr<Chunk> chunkToGenerate = chunks[i];
						std::thread th([chunkToGenerate]() {
							if (chunkToGenerate) {
								chunkToGenerate->generate();
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
		}
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
			std::shared_ptr<Chunk>* tempChunks = new std::shared_ptr<Chunk>[new_chunks_world_count];
			for (int x = -new_render_distance; x <= new_render_distance; ++x) {
				for (int z = -new_render_distance; z <= new_render_distance; ++z) {
					int i = ((x + new_render_distance) * new_chunks_world_width) + z + new_render_distance;
					if (x >= -render_distance && x <= render_distance && z >= -render_distance && z <= render_distance) {
						int old_i = ((x + render_distance) * chunks_world_width) + z + render_distance;
						tempChunks[i] = chunks[old_i];
						tempChunks[i]->setMoved(true);
					}
					else {
						tempChunks[i] = std::make_shared<Chunk>(this, glm::ivec2(x, z), heroChunkPos + glm::ivec2(x, z));
					}
				}
			}
			for (unsigned int i = 0; i < chunks_world_count; ++i) {
				if(chunks[i]->isMoved()){
					chunks[i]->setMoved(false);
				}
				else {
					chunks[i]->setForDelete(true);
					chunks[i]->finalization();
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
		std::shared_ptr<Chunk>* tempChunks = new std::shared_ptr<Chunk>[chunks_world_count];
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
					chunks[i]->setForDelete(true);
					chunks[i]->finalization();
				}
			}
		}

		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				if (tempChunks[i] == nullptr) {
					tempChunks[i] = std::make_shared<Chunk>(this, glm::ivec2(x, z), heroChunkPos + glm::ivec2(x, z));
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
}
