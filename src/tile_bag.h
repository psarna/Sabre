#ifndef __TILE_BAG_H
#define __TILE_BAG_H

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

class TileBag {
public:
	static const int kMaxQuantity = 64;

	typedef char Tile;
	static const Tile kNoTile = 0;

	typedef std::vector<Tile> TileList;

	TileBag(const std::string &tiles) : tiles_(tiles.begin(), tiles.end()) {
		std::random_shuffle(tiles_.begin(), tiles_.end());
	}

	Tile get() {
		assert(!tiles_.empty());
		Tile ret = tiles_.back();
		tiles_.pop_back();
		return ret;
	}

	bool empty() const {
		return tiles_.empty();
	}

	friend std::ostream &operator<<(std::ostream &os, const TileBag &bag) {
		for (auto &tile : bag.tiles_) {
			os << "[" << (tile == kNoTile ? ' ' : tile) << "]";
		}
		return os;
	}

private:
	TileList tiles_;
};

#endif