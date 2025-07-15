#pragma once

#include <vector>
#include <string>

namespace bulka {
	class Block;
	class BlocksManager{
	private:
		static std::vector<Block*> blocks;
	protected:
	public:
		static void init();
		static void finalization();
		static Block* getBlock(unsigned short id);
		static Block* getBlock(std::string name);
	};

}

