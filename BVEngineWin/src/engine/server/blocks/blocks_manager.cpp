#include "blocks_manager.h"

#include "block.h"

namespace bulka {
	std::vector<Block*> BlocksManager::blocks;
	void BlocksManager::init() {
		blocks.clear();
		unsigned short id = 0;
		blocks.push_back(nullptr);
		blocks.push_back(new Block(++id, "stone"));
	}
	void BlocksManager::finalization() {
		for (auto block : blocks) {
			delete block;
		}
		blocks.clear();
	}
	Block* BlocksManager::getBlock(unsigned short id)
	{
		return blocks[id];
	}
	Block* BlocksManager::getBlock(std::string name)
	{
		for (auto block : blocks) {
			if (name.compare(block->name) == 0) {
				return block;
			}
		}
		return nullptr;
	}
}