#pragma once

namespace uth {

	class State {
	public:
		State(unsigned int numPlayers);
		~State() {}

		State(State const&) = delete;

		unsigned int CurrentPlayer();
		unsigned int NextPlayer();
		unsigned int NumPlayers();

	private:
		unsigned int numPlayers;
		unsigned int currentPlayer;
	};

}
