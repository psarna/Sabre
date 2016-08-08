#ifndef __BOARD_H
#define __BOARD_H

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "dictionary.h"
#include "dir.h"
#include "field.h"
#include "tile_bag.h"


class Board {
public:
	typedef TileBag::Tile Tile;
	typedef Dictionary::Word Word;

	Board(int height, int width);

	int width() const {
		return width_;
	}

	int height() const {
		return height_;
	}

	Field &at(int x, int y);
	const Field &at(int x, int y) const;
	void put(int x, int y, Tile tile);

	friend std::ostream &operator<<(std::ostream &os, const Board &board);

protected:
	int height_;
	int width_;
	std::vector<Field> fields_;
};

#endif
