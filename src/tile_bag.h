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

	typedef std::vector<Tile> TileList;

	TileBag(TileList &&tiles) noexcept : tiles_(tiles) {
		std::random_shuffle(tiles_.begin(), tiles_.end());
	}

	TileBag(const std::string &path) {
		std::ifstream fs(path);
		std::string line;

		while (std::getline(fs, line)) {
			Tile tile;
			int quantity;
			if (std::sscanf(line.c_str(), "%c %d", &tile, &quantity) != 2
				|| quantity < 0 || quantity > kMaxQuantity || !std::isalpha(tile)) {
				throw std::runtime_error("incorrect tilebag format");
			}
			for (int i = 0; i < quantity; ++i) {
				tiles_.push_back(tile);
			}
		}

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

private:
	TileList tiles_;
};

#endif