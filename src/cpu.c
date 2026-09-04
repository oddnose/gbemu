#include <stdio.h>
#include <stdlib.h>
#include "op/cb_lookup.h"
#include "op/instruction_result.h"
#include "op/op_definition.h"
#include "state.h"
#include "op/op_lookup.h"


struct Cpu {
	unsigned char cycles_to_next_instruction;
};

struct Cpu* create_cpu()
{
	struct Cpu* cpu = malloc(sizeof *cpu);

	cpu->cycles_to_next_instruction = 0;

	return cpu;
}

void print_instruction(struct State* state, struct OpDefinition def, uint8_t pos)
{
	printf("%04x\t", pos);
	for (uint8_t i = 0; i < def.length; i++) {
		printf("%02x ", read_char(state, pos + i));
	}

	if (def.length == 3) {
		printf("\t");
	} else {
		printf("\t\t");
	}

	switch (def.length - 1) {
		case 0: {
			printf("%s", def.format_name);
			break;
		}
		case 1: {
			printf(def.format_name, read_char(state, pos + 1));
			break;
		}
		case 2: {
			printf(def.format_name, read_short(state, pos + 1));
			break;
		}
	}
	printf("\n");
}

void print_memory_updates(struct MemoryUpdate* updates, unsigned char num_updates)
{
	for (int i = 0; i < num_updates; i++) {
		switch (updates[i].location) {
			case RegA: { printf("A: $%02x -> $%02x\n", updates[i].old_val_8bit, updates[i].new_val_8bit); break; }
			case RegB: { printf("B: $%02x -> $%02x\n", updates[i].old_val_8bit, updates[i].new_val_8bit); break; }
			case RegC: { printf("C: $%02x -> $%02x\n", updates[i].old_val_8bit, updates[i].new_val_8bit); break; }
			case RegD: { printf("D: $%02x -> $%02x\n", updates[i].old_val_8bit, updates[i].new_val_8bit); break; }
			case RegE: { printf("E: $%02x -> $%02x\n", updates[i].old_val_8bit, updates[i].new_val_8bit); break; }
			case RegH: { printf("H: $%02x -> $%02x\n", updates[i].old_val_8bit, updates[i].new_val_8bit); break; }
			case RegL: { printf("L: $%02x -> $%02x\n", updates[i].old_val_8bit, updates[i].new_val_8bit); break; }
			case RegBC: { printf("BC: $%04x -> $%04x\n", updates[i].old_val_16bit, updates[i].new_val_16bit); break; }
			case RegDE: { printf("DE: $%04x -> $%04x\n", updates[i].old_val_16bit, updates[i].new_val_16bit); break; }
			case RegHL: { printf("HL: $%04x -> $%04x\n", updates[i].old_val_16bit, updates[i].new_val_16bit); break; }
			case StackPointer: { printf("SP: $%04x -> $%04x\n", updates[i].old_val_16bit, updates[i].new_val_16bit); break; }
			case ProgramCounter: { printf("PC: $%04x -> $%04x\n", updates[i].old_val_16bit, updates[i].new_val_16bit); break; }
			case ZFlag: { printf("Z flag: %d -> %d\n", updates[i].old_val_1bit, updates[i].new_val_1bit); break; }
			case NFlag: { printf("N flag: %d -> %d\n", updates[i].old_val_1bit, updates[i].new_val_1bit); break; }
			case HFlag: { printf("H flag: %d -> %d\n", updates[i].old_val_1bit, updates[i].new_val_1bit); break; }
			case CFlag: { printf("C flag: %d -> %d\n", updates[i].old_val_1bit, updates[i].new_val_1bit); break; }
			case Address: { printf("Address $%04x: $%02x -> $%02x\n", updates[i].address, updates[i].old_val_1bit, updates[i].new_val_1bit); break; }
		}
	}
}

void cpu_tick(struct Cpu* cpu, struct State* state)
{
	if (cpu->cycles_to_next_instruction == 0) {
		struct OpDefinition def;
		def = decode(state, read_reg_16bit(state, ProgramCounter));
		//print_instruction(state, def, read_reg_16bit(state, ProgramCounter));
		if (!def.callback) {
			printf("Instruction not implemented!");
		}
		struct InstructionResult result = def.callback(state);
		//print_memory_updates(result.updates, result.num_memory_updates);
		free(result.updates);
		//printf("\n");
		if (read_reg_16bit(state, ProgramCounter) == 0x00E9) {
			exit(0);
		}

		cpu->cycles_to_next_instruction = result.cycles; 
	} else {
		cpu->cycles_to_next_instruction--;
	}
}
