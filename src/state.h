#ifndef STATE_H
#define STATE_H

struct State {
	unsigned char memory[8000];
	unsigned short program_counter;
	unsigned short stack_pointer;
};

#endif
