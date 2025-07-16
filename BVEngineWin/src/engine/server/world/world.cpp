#include "world.h"

#include "chunks/chunk.h"
#include "../../graphics/texture_manager.h"
#include "../../graphics/shader_manager.h"
#include "../../settings.h"
#include <iostream>

namespace bulka {
	bcppul::Logger* World::logger = bcppul::getLogger("World");
	World::World()
	{
	}
	World::~World()
	{
		if(chunks != nullptr){
			for (unsigned int i = 0; i < chunks_world_count; ++i) {
				chunks[i]->finalization();
				delete chunks[i];
			}
			delete[] chunks;
			chunks = nullptr;
		}
	}

	void World::load() {
		setRenderDistance(Settings::RENDER_DISTANCE);
		chunks = new Chunk* [chunks_world_count];
		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				unsigned int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				chunks[i] = new Chunk(this, glm::ivec2(x, z));
			}
		}
		generate();

	}
	void World::generate() {
		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				unsigned int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				chunks[i]->generate();
			}
		}
	}
	void World::reload() {
		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				unsigned int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				chunks[i]->createMeshes();
			}
		}
	}
	void World::update() {

	}
	void World::render() {
		ShaderManager::chunkShader.bind();
		TextureManager::bindTexture("res/textures/blocks.png");
		for (int x = -render_distance; x <= render_distance; ++x) {
			for (int z = -render_distance; z <= render_distance; ++z) {
				unsigned int i = ((x + render_distance) * chunks_world_width) + z + render_distance;
				chunks[i]->render();
			}
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
			Chunk** tempChunks = new Chunk*[new_chunks_world_count];
			for (int x = -new_render_distance; x <= new_render_distance; ++x) {
				for (int z = -new_render_distance; z <= new_render_distance; ++z) {
					int i = ((x + new_render_distance) * new_chunks_world_width) + z + new_render_distance;
					if (i == -1) {
						i = new_chunks_world_count;
					}
					if (x >= -render_distance && x <= render_distance && z >= -render_distance && z <= render_distance) {
						int old_i = ((x + render_distance) * chunks_world_width) + z + render_distance;
						tempChunks[i] = chunks[old_i];
						tempChunks[i]->setMoved(true);
					}
					else {
						tempChunks[i] = new Chunk(this, glm::ivec2(x, z));
					}
				}
			}
			for (unsigned int i = 0; i < chunks_world_count; ++i) {
				if(chunks[i]->isMoved()){
					chunks[i]->setMoved(false);
				}
				else {
					chunks[i]->finalization();
					delete chunks[i];
				}
			}
			for (unsigned int i = 0; i < new_chunks_world_count; i++)
			{
				if (!tempChunks[i]->isGenerated())
				{
					tempChunks[i]->generate();
				}
			}
			delete[] chunks;
			chunks = tempChunks;
		}
		render_distance = new_render_distance;
		chunks_world_width = new_chunks_world_width;
		chunks_world_count = new_chunks_world_count;
	}
}
