#include "game_controller.h"

extern "C" {
	void *create(int x, int y, const char *dict_path, const char *tiles) {
		return new GameController(x, y, dict_path, tiles);
	}

	void destroy(GameController *ptr) {
		delete ptr;
	}

	char get_tile(GameController *ptr, int x, int y) {
		return ptr->board().at(x, y).tile;
	}
}
