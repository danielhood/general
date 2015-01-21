#pragma once

#include <thread>
#include <memory>
#include "state.h"


using namespace std;

// Some ref for threads: http://stackoverflow.com/questions/5956759/c11-stdthread-inside-a-class-executing-a-function-member-with-thread-initia?rq=1

namespace uth {
	
	class Command {
	public:
		Command(shared_ptr<State> const& state);
		//Command(State &state);
		~Command() {}

		Command(Command const&) = delete;		
		Command& operator =(Command const&) = delete;

		void Run();
		void Wait();

	private:
		thread commandThread;
		shared_ptr<State> state;
		//State* state;

		void Loop();
		
	};
}
