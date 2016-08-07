#include "board.h"
#include <cstdio>
#include <iostream>

typedef Board<6, 8> GameBoard;
typedef GameBoard::Field Field;
typedef GameBoard::Move Move;

int main() {
	GameBoard &board = GameBoard::instance();

	board.put(2, 4, 'a');
	board.put(3, 4, 'b');
	board.put(4, 4, 'a');
	board.put(5, 4, 'k');

	board.put(2, 3, 'e');
	board.put(2, 5, 'i');
	board.put(2, 6, 'g');

	std::cout << board.getWord(board.at(3, 4), GameBoard::kEast) << std::endl;
	std::cout << board.getWord(board.at(3, 4), GameBoard::kSouth) << std::endl;

	Move move;
	move.add(board.at(2, 4));
	move.add(board.at(3, 4));
	move.add(board.at(4, 4));
	move.add(board.at(5, 4));
	std::cout << std::boolalpha << move.adjacent() << move.consistent(GameBoard::kEast) << move.consistent(GameBoard::kSouth) << move.valid() << std::endl;

	board.print();
}
