#include "blocks_manager.h"

#include "block.h"

namespace bulka {
	std::vector<Block*> BlocksManager::blocks;
	void BlocksManager::init() {
		blocks.clear();
		unsigned short id = 0;
		blocks.push_back(nullptr);
		Block* stone = new Block(++id, "stone", false,
			*Block::Face(Block::defaultFaceBack).setTextureX(0)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceFront).setTextureX(0)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceLeft).setTextureX(0)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceRight).setTextureX(0)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceBottom).setTextureX(0)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceTop).setTextureX(0)->setTextureY(0)->recalcVertices()
		);
		blocks.push_back(stone);
		Block* dirt = new Block(++id, "dirt", false, 
			*Block::Face(Block::defaultFaceBack).setTextureX(3)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceFront).setTextureX(3)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceLeft).setTextureX(3)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceRight).setTextureX(3)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceBottom).setTextureX(3)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceTop).setTextureX(3)->setTextureY(0)->recalcVertices()
		);
		blocks.push_back(dirt);
		Block* grass = new Block(++id, "grass", false,
			*Block::Face(Block::defaultFaceBack).setTextureX(1)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceFront).setTextureX(1)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceLeft).setTextureX(1)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceRight).setTextureX(1)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceBottom).setTextureX(3)->setTextureY(0)->recalcVertices(),
			*Block::Face(Block::defaultFaceTop).setTextureX(2)->setTextureY(0)->recalcVertices()
		);
		blocks.push_back(grass);
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