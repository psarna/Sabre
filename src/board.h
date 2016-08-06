#ifndef __BOARD_H
#define __BOARD_H

#include <array>

template<int Height, int Width>
class Board {
static_assert(Height > 0 && Width > 0, "Board size must be positive.");
public:
	static const int kHeight = Height;
	static const int kWidth = Width;
	typedef char Tile;

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
			static Field null_field{-1, -1, -1, kWrong};
			return null_field;
		}
	};

	static Board &instance() {
		static Board board;
		return board;
	}

	Field &at(int x, int y) {
		return fields_[x * Width + y];
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
