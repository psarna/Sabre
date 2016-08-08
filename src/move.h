#ifndef __MOVE_H
#define __MOVE_H

#include "field.h"

class Move {
public:
	void add(const Field &field) {
		fields_.push_back(&field);
	}

	Dir getDir() const {
		int x = fields_[0]->x;
		int y = fields_[0]->y;
		bool horizontal = true;
		bool vertical = true;

		for (size_t i = 0; i < fields_.size(); ++i)
			if (fields_[i]->x != x)
				horizontal = false;

		for (size_t i = 0; i < fields_.size(); ++i)
			if (fields_[i]->y != y)
				vertical = false;

		return horizontal ? kEast : vertical ? kSouth : kWrong;
	}

	bool contains(const Field &field) const {
		return std::find_if(fields_.begin(), fields_.end(),
			[&field](const Field *ptr){return field == *ptr;}) != fields_.end();
	}

	bool consistent(Dir dir, Board &board) const {
		assert(dir == kEast || dir == kSouth);
		auto min_x_it = std::min_element(fields_.begin(), fields_.end(),
									[](const Field *f1, const Field *f2) {return f1->x < f2->x;});
		auto min_y_it = std::min_element(fields_.begin(), fields_.end(),
									[](const Field *f1, const Field *f2) {return f1->y < f2->y;});
		size_t used = 0;

		const Field *field = dir == kSouth ? *min_x_it : *min_y_it;
		while (*field != Field::null()) {
			used += contains(*field);
			field = &field->neighbour(dir, board);
		}

		return fields_.size() == used;
	}

	bool adjacent(Board &board) const {
		int neighbour_count = 0;
		for (size_t i = 0; i < fields_.size(); ++i) {
			for (int dir = kNorth; dir < kWrong; ++dir) {
				neighbour_count += fields_[i]->neighbour((Dir)dir, board).tile != TileBag::kNoTile;
			}
		}
		return (size_t)neighbour_count > 2 * fields_.size() - 2;
	}

	bool valid(Board &board) const {
		if (fields_.empty()) {
			return false;
		}

		Dir dir = getDir();
		if (dir == kWrong) {
			return false;
		}

		return consistent(dir, board) && adjacent(board);
	}

private:
	std::vector<const Field *> fields_;
};

#endif
