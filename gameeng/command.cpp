#include "command.h"
#include <iostream>

using namespace std;
using namespace uth;

Command::Command(shared_ptr<State> const& state) : 
//Command::Command(State &state) : 
	commandThread(), state(state) {
}

void Command::Run() {
	commandThread = thread(&Command::Loop, this);
}

void Command::Wait() {
	commandThread.join();
}

void Command::Loop() {
	bool isDone = false;
	string command = {};

	while(!isDone) {
		cout << "gameng> ";
		cin >> command;
		if (command.compare("exit") == 0) {
			isDone = true;
		} else if (command.compare("player") == 0) {
			cout << "Current player: " << state->CurrentPlayer() << endl;
		} else if (command.compare("next") == 0) {
			cout << "Next player: " << state->NextPlayer() << endl;
		}

	}
}

