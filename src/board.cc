#include "board.h"
#include "field.h"

Board::Board(int height, int width) : height_(height), width_(width), fields_(width * height) {
	assert(width > 0 && height > 0);
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			Field &field = at(i, j);
			field.x = i;
			field.y = j;
		}
	}
}

Field &Board::at(int x, int y) {
	return fields_[x * width_ + y];
}

const Field &Board::at(int x, int y) const {
	return fields_[x * width_ + y];
}

void Board::put(int x, int y, Tile tile) {
	at(x, y).tile = tile;
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
	for (int i = 0; i < board.height(); ++i) {
		for (int j = 0; j < board.width(); ++j) {
			const Field &field = board.at(i, j);
			os << field;
		}
		os << std::endl;
	}
	return os;
}
