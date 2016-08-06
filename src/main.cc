#include "board.h"
#include <cstdio>

typedef Board<6, 8> GameBoard;
typedef GameBoard::Field Field;

int main() {
	GameBoard &board = GameBoard::instance();

	for (int i = 0; i < GameBoard::kHeight; ++i) {
		for (int j = 0; j < GameBoard::kWidth; ++j) {
			Field &field = board.at(i, j);
			printf("(%d,%d)", field.x, field.y);
		}
		printf("\n");
	}
}
