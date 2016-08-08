#ifndef __FIELD_H
#define __FIELD_H

#include "dictionary.h"
#include "tile_bag.h"
#include "dir.h"

class Board;

struct Field {
	typedef TileBag::Tile Tile;
	typedef Dictionary::Word Word;

	enum Type {
		kNormal, kBonus, kDoubleBonus, kStart, kDestination, kWrong
	};

	int x;
	int y;
	Tile tile;
	Type type;

	Field &neighbour(Dir dir, Board &board) const;
	Word getWord(Dir dir, Board &board) const;

	static Field &null() {
		static Field null_field{-1, -1, TileBag::kNoTile, kWrong};
		return null_field;
	}

	bool operator==(const Field &other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Field &other) const {
		return x != other.x || y != other.y;
	}

	friend inline std::ostream &operator<<(std::ostream &os, const Field &f) {
		os << "[" << (f.tile == TileBag::kNoTile ? ' ' : f.tile) << "]";
		return os;
	}
};

#endif
