#pragma once

#include <vector>
#include <bcppul/logging.h>


namespace bulka {
	class Chunk;
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
		void setRenderDistance(int val);
	};

}

