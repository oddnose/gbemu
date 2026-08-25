#include "cb_lookup.h"
#include <stdio.h>
#include <stdlib.h>
#include "op/op_definition.h"
#include "rotate_instructions.h"

void cb_not_implemented(struct State* state)
{
	printf("Unknown CB instruction: $%02x\n", state->memory[state->program_counter]);
	exit(1);
}

// Initialize lookup table with function pointers
struct OpDefinition cb_lookup[256] = {
	[0x00] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x01] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x02] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x03] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x04] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x05] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x06] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x07] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x08] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x09] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x0a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x0b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x0c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x0d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x0e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x0f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x10] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x11] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x12] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x13] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x14] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x15] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x16] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x17] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x18] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x19] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x1a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x1b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x1c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x1d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x1e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x1f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x20] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x21] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x22] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x23] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x24] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x25] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x26] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x27] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x28] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x29] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x2a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x2b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x2c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x2d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x2e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x2f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x30] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x31] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x32] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x33] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x34] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x35] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x36] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x37] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x38] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x39] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x3a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x3b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x3c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x3d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x3e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x3f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x40] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x41] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x42] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x43] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x44] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x45] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x46] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x47] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x48] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x49] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x4a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x4b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x4c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x4d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x4e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x4f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x50] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x51] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x52] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x53] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x54] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x55] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x56] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x57] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x58] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x59] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x5a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x5b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x5c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x5d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x5e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x5f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x60] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x61] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x62] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x63] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x64] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x65] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x66] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x67] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x68] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x69] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x6a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x6b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x6c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x6d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x6e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x6f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x70] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x71] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x72] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x73] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x74] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x75] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x76] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x77] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x78] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x79] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x7a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x7b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x7c] = {
		"BIT 7, H",
		.length = 2,
		.callback = op_bit_7_h
	},
	[0x7d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x7e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x7f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x80] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x81] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x82] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x83] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x84] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x85] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x86] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x87] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x88] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x89] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x8a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x8b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x8c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x8d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x8e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x8f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x90] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x91] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x92] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x93] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x94] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x95] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x96] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x97] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x98] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x99] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x9a] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x9b] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x9c] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x9d] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x9e] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0x9f] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa0] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa1] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa2] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa3] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa4] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa5] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa6] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa7] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa8] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xa9] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xaa] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xab] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xac] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xad] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xae] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xaf] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb0] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb1] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb2] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb3] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb4] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb5] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb6] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb7] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb8] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xb9] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xba] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xbb] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xbc] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xbd] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xbe] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xbf] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc0] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc1] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc2] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc3] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc4] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc5] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc6] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc7] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc8] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xc9] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xca] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xcb] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xcc] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xcd] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xce] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xcf] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd0] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd1] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd2] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd3] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd4] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd5] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd6] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd7] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd8] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xd9] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xda] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xdb] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xdc] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xdd] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xde] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xdf] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe0] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe1] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe2] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe3] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe4] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe5] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe6] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe7] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe8] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xe9] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xea] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xeb] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xec] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xed] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xee] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xef] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf0] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf1] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf2] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf3] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf4] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf5] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf6] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf7] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf8] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xf9] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xfa] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xfb] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xfc] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xfd] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xfe] = {
		.length = 2,
		.callback = cb_not_implemented
	},
	[0xff] = {
		.length = 2,
		.callback = cb_not_implemented
	}
};

struct OpDefinition cb_decode(struct State* state, uint8_t pos)
{
	return cb_lookup[state->memory[pos]];
}
