#include <cstdio>
#include <iostream>

#include "board.h"
#include "dictionary.h"
#include "tile_bag.h"

typedef Board<6, 8> GameBoard;
typedef GameBoard::Field Field;
typedef GameBoard::Move Move;
typedef GameBoard::Player Player;

int main() {
	srand(0x10);
	GameBoard &board = GameBoard::instance();
	TileBag tile_bag(
		"aaaabbbbccddeeffghiiiijklllmmnnooopppqrrsstttuwwxyzz"
	);
	Dictionary dictionary(
		{"abak", "eig", "asan"}
	);

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

	std::cout << dictionary.has("aids") << dictionary.has("abak") << std::endl;

	Player player;
	while (!tile_bag.empty() && player.canTakeTile()) {
		player.takeTile(tile_bag);
		player.printHand();
	}

	player.putTile(2, board.at(1, 1));
	player.putTile(4, board.at(2, 2));
	player.putTile(3, board.at(2, 2));
	board.print();
	player.printHand();

	player.takeTile(board.at(2, 2));
	player.takeTile(board.at(1, 1));
	player.putTile(2, board.at(0, 0));
	player.putTile(6, board.at(0, 0));
	player.putTile(3, board.at(0, 1));

	board.print();
	player.printHand();
}
