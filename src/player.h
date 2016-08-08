#ifndef __PLAYER_H
#define __PLAYER_H

#include "board.h"
#include "move.h"

class Player {
public:
	typedef TileBag::Tile Tile;
	static const int kMaxHand = 7;
	typedef std::array<Tile, kMaxHand> Hand;

	Player(const std::string &name) : name_(name), hand_(), move_() {}

	Tile getTile(int i) const {
		assert(i >= 0 && i < kMaxHand);
		return hand_[i];
	}

	bool canPutTile(int tile_index, Field &field) {
		return (field.tile == TileBag::kNoTile || move_.contains(field))
				&& getTile(tile_index) != TileBag::kNoTile;
	}

	void putTile(int tile_index, Field &field) {
		assert(canPutTile(tile_index, field));
		std::swap(field.tile, hand_[tile_index]);
		if (!move_.contains(field)) {
			move_.add(field);
		}
	}

	bool canTakeTile() const {
		return tileCount() != kMaxHand;
	}

	bool canTakeTile(Field &field) const {
		return move_.contains(field);
	}

	void takeTile(TileBag &tile_bag) {
		assert(canTakeTile());
		auto it = std::find(hand_.begin(), hand_.end(), (Tile)TileBag::kNoTile);
		assert(it != hand_.end());
		*it = tile_bag.get();
	}

	void takeTile(Field &field) {
		assert(canTakeTile());
		auto it = std::find(hand_.begin(), hand_.end(), (Tile)TileBag::kNoTile);
		assert(it != hand_.end());
		std::swap(*it, field.tile);
	}

	const Hand &hand() const {
		return hand_;
	}

	Move &getMove() {
		return move_;
	}

	const Move &getMove() const {
		return move_;
	}

	int tileCount() const {
		return kMaxHand - std::count(hand_.begin(), hand_.end(), (Tile)TileBag::kNoTile);
	}

	friend std::ostream &operator<<(std::ostream &os, const Player &player) {
		for (auto it = player.hand_.begin(); it != player.hand_.end(); ++it) {
			os << (*it == TileBag::kNoTile ? '-' : *it);
		}
		return os;
	}

private:
	std::string name_;
	Hand hand_;
	Move move_;
};

#endif
