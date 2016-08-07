#ifndef __BOARD_H
#define __BOARD_H

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <functional>
#include <string>
#include <vector>

template<int Height, int Width>
class Board {
static_assert(Height > 0 && Width > 0, "Board size must be positive.");
public:
	static const int kHeight = Height;
	static const int kWidth = Width;

	typedef char Tile;
	static const Tile kNoTile = 0;
	typedef std::string Word;

	enum Dir {
		kNorth, kEast, kSouth, kWest, kWrong
	};

	struct Field {
		enum Type {
			kNormal, kBonus, kDoubleBonus, kStart, kDestination, kWrong
		};

		int x;
		int y;
		Tile tile;
		Type type;

		Field &neighbour(Dir dir) const {
			switch (dir) {
			case kNorth:
				return x > 0 ? Board::instance().at(x - 1, y) : null();
			case kEast:
				return y < Board::kWidth - 1 ? Board::instance().at(x, y + 1) : null();
			case kSouth:
				return x < Board::kHeight - 1 ? Board::instance().at(x + 1, y) : null();
			case kWest:
				return y > 0 ? Board::instance().at(x, y - 1) : null();
			default:
				return null();
			}
		}

		static Field &null() {
			static Field null_field{-1, -1, kNoTile, kWrong};
			return null_field;
		}

		bool operator==(const Field &other) const {
			return x == other.x && y == other.y;
		}

		bool operator!=(const Field &other) const {
			return x != other.x || y != other.y;
		}
	};

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

		bool consistent(Dir dir) const {
			assert(dir == kEast || dir == kSouth);
			auto min_x_it = std::min_element(fields_.begin(), fields_.end(),
										[](const Field *f1, const Field *f2) {return f1->x < f2->x;});
			auto min_y_it = std::min_element(fields_.begin(), fields_.end(),
										[](const Field *f1, const Field *f2) {return f1->y < f2->y;});
			size_t used = 0;

			const Field *field = dir == kSouth ? *min_x_it : *min_y_it;
			while (*field != Field::null()) {
				used += contains(*field);
				field = &field->neighbour(dir);
			}

			return fields_.size() == used;
		}

		bool adjacent() const {
			int neighbour_count = 0;
			for (size_t i = 0; i < fields_.size(); ++i) {
				for (int dir = kNorth; dir < kWrong; ++dir) {
					neighbour_count += fields_[i]->neighbour((Dir)dir).tile != kNoTile;
				}
			}
			return (size_t)neighbour_count > 2 * fields_.size() - 2;
		}

		bool valid() const {
			if (fields_.empty()) {
				return false;
			}

			Dir dir = getDir();
			if (dir == kWrong) {
				return false;
			}

			return consistent(dir) && adjacent();
		}

	private:
		std::vector<const Field *> fields_;
	};

	Field &at(int x, int y) {
		return fields_[x * Width + y];
	}

	const Field &at(int x, int y) const {
		return fields_[x * Width + y];
	}

	Word getWord(const Field &field, Dir dir) const {
		assert(dir == kSouth || dir == kEast);
		int x = field.x;
		int y = field.y;
		int delta_x = dir == kSouth ? 1 : 0;
		int delta_y = dir == kEast ? 1 : 0;
		Word word;

		while (x >= 0 && y >= 0 && at(x, y).tile != kNoTile) {
			x -= delta_x;
			y -= delta_y;
		}
		x += delta_x;
		y += delta_y;

		while (x < kHeight && y < kWidth && at(x, y).tile != kNoTile) {
			word += at(x, y).tile;
			x += delta_x;
			y += delta_y;
		}

		return word;
	}

	void put(int x, int y, Tile tile) {
		at(x, y).tile = tile;
	}

	void print() const {
		for (int i = 0; i < kHeight; ++i) {
			for (int j = 0; j < kWidth; ++j) {
				const Field &field = at(i, j);
				printf("[%c]", field.tile != kNoTile ? field.tile : ' ');
			}
			printf("\n");
		}
	}

	static Board &instance() {
		static Board board;
		return board;
	}

protected:
	Board() : fields_() {
		for (int i = 0; i < kHeight; ++i) {
			for (int j = 0; j < kWidth; ++j) {
				Field &field = at(i, j);
				field.x = i;
				field.y = j;
			}
		}
	}

	std::array<Field, Width * Height> fields_;
};

#endif
