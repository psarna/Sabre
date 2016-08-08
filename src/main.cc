#include <cstdio>
#include <iostream>

#include "board.h"
#include "dictionary.h"
#include "tile_bag.h"
#include "move.h"
#include "player.h"

int main() {
	srand(0x10);
	Board board(6, 8);
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

	std::cout << board.at(3, 4).getWord(kEast, board) << std::endl;
	std::cout << board.at(3, 4).getWord(kSouth, board) << std::endl;

	Move move;
	move.add(board.at(2, 4));
	move.add(board.at(3, 4));
	move.add(board.at(4, 4));
	move.add(board.at(5, 4));
	std::cout << std::boolalpha << move.adjacent(board) << move.consistent(kEast, board) << move.consistent(kSouth, board) << move.valid(board) << std::endl;

	std::cout << dictionary.has("aids") << dictionary.has("abak") << std::endl;

	Player player;
	while (!tile_bag.empty() && player.canTakeTile()) {
		player.takeTile(tile_bag);
		std::cout << player << std::endl;;
	}

	player.putTile(2, board.at(1, 1));
	player.putTile(4, board.at(2, 2));
	player.putTile(3, board.at(2, 2));
	std::cout << board;
	std::cout << player << std::endl;;

	player.takeTile(board.at(2, 2));
	player.takeTile(board.at(1, 1));
	player.putTile(2, board.at(0, 0));
	player.putTile(6, board.at(0, 0));
	player.putTile(3, board.at(0, 1));

	std::cout << board;
	std::cout << player << std::endl;;
}
