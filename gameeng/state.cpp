#include "state.h"

namespace uth {
	State::State(unsigned int numPlayers) {
		this->numPlayers = numPlayers;
		this->currentPlayer = 0;
	}

	unsigned int State::NumPlayers() {
		return this->numPlayers;
	}

	unsigned int State::CurrentPlayer() {
		return this->currentPlayer;
	}

	unsigned int State::NextPlayer() {
		return ++this->currentPlayer%=this->numPlayers;
	}
}
