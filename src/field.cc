#include "board.h"
#include "field.h"

Field &Field::neighbour(Dir dir, Board &board) const {
	switch (dir) {
	case kNorth:
		return x > 0 ? board.at(x - 1, y) : null();
	case kEast:
		return y < board.width() - 1 ? board.at(x, y + 1) : null();
	case kSouth:
		return x < board.height() - 1 ? board.at(x + 1, y) : null();
	case kWest:
		return y > 0 ? board.at(x, y - 1) : null();
	default:
		return null();
	}
}

Field::Word Field::getWord(Dir dir, Board &board) const {
	assert(dir == kSouth || dir == kEast);
	int current_x = x;
	int current_y = y;
	int delta_x = dir == kSouth ? 1 : 0;
	int delta_y = dir == kEast ? 1 : 0;
	Word word;

	while (current_x >= 0 && current_y >= 0 && board.at(current_x, current_y).tile != TileBag::kNoTile) {
		current_x -= delta_x;
		current_y -= delta_y;
	}
	current_x += delta_x;
	current_y += delta_y;

	while (current_x < board.height() && current_y < board.width()
		&& board.at(current_x, current_y).tile != TileBag::kNoTile) {
		word += board.at(current_x, current_y).tile;
		current_x += delta_x;
		current_y += delta_y;
	}

	return word;
}

