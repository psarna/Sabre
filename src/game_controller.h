#ifndef __GAME_CONTROLLER_H
#define __GAME_CONTROLLER_H

#include "board.h"
#include "field.h"
#include "move.h"
#include "player.h"
#include "tile_bag.h"

class GameController {
public:
	typedef TileBag::Tile Tile;
	typedef Dictionary::Word Word;
	typedef Dictionary::WordSet WordSet;

	GameController(Board &board, Dictionary &dictionary, TileBag &tile_bag)
		: board_(board), dictionary_(dictionary), tile_bag_(tile_bag) {}

	void addPlayer(std::string name) {
		players_.emplace_back(name);
		active_player_ = players_.begin();
	}

	void nextPlayer() {
		active_player_++;
		if (active_player_ == players_.end()) {
			active_player_ = players_.begin();
		}
	}

	void pickTile(int i) {
		active_tile_index_ = i;
	}

	bool canPutTile(int x, int y) {
		return active_player_->canPutTile(active_tile_index_, board_.at(x, y));
	}

	void putTile(int x, int y) {
		active_player_->putTile(active_tile_index_, board_.at(x, y));
		active_tile_index_ = -1;
	}

	void gatherTiles() {
		while (!tile_bag_.empty() && active_player_->canTakeTile()) {
			active_player_->takeTile(tile_bag_);
		}
	}

	Player &getActivePlayer() {
		return *active_player_;
	}

	Tile getActiveTileIndex() {
		return active_tile_index_;
	}

	Board &board() {
		return board_;
	}

	TileBag &tileBag() {
		return tile_bag_;
	}

	bool canCommit() {
		bool valid;
		if (first_move_) {
			valid = active_player_->getMove().validAsFirst(board_);
		} else {
			valid = active_player_->getMove().valid(board_);
		}
		return valid && isMoveCorrect();
	}
	void commit() {
		//TODO: Add points
		active_player_->getMove().clear();
		if (first_move_) {
			first_move_ = false;
		}
	}
	void rollback() {
		auto &fields = active_player_->getMove().fields();
		for (auto &field : fields) {
			active_player_->takeTile(*field);
		}
	}

	bool isMoveCorrect() {
		size_t max_length = 0;
		WordSet words = active_player_->getMove().getWords(board_);
		if (words.empty()) {
			return false;
		}

		for (auto it = words.begin(); it != words.end(); ++it) {
			max_length = std::max(max_length, it->length());
		}

		for (auto it = words.begin(); it != words.end(); ++it) {
			if (it->length() > 1 && !dictionary_.has(*it)) {
				return false;
			}
		}

		return true;
	}

	void flushTiles() {}

private:
	void nextRound();
	Board &board_;
	Dictionary &dictionary_;
	TileBag &tile_bag_;
	std::vector<Player>::iterator active_player_;
	Field *active_field_;
	int active_tile_index_;
	std::vector<Player> players_;
	bool first_move_;
};

#endif
