#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include "state.h"
#include "command.h"

using namespace std;
using namespace uth;

int main(void)
{
	cout << "gameng v1.0" << endl << endl;

	shared_ptr<State> state = make_shared<State>(2);
	//State state(2);

	cout << "There are " << state->NumPlayers() << " players in the game." << endl;

	Command command(state);
	command.Run();
	command.Wait();

	cout << "Last player: " << state->CurrentPlayer() << endl;

	return 0;
}
