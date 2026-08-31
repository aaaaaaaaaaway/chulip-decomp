typedef unsigned int u32;

typedef struct PacketState {
    u32 current;
    u32 limit;
    u32 count;
} PacketState;

typedef struct PacketCursor {
    u32 *current;
    u32 *limit;
    u32 count;
} PacketCursor;

extern u32 D_002D81D0;

void func_00161230(PacketState *state, u32 count, u32 flags)
{
    u32 address = (u32)&D_002D81D0;

    state->current = address;
    if (address != 0) {
        address |= flags;
        state->count = count;
        state->current = address;
        state->limit = address;
    }
}

void func_00161258(PacketCursor *cursor)
{
    u32 *tag = cursor->current;

    cursor->limit = tag;
    tag[0] = 0x70000000;
    tag[2] = 0;
    tag[1] = 0;
    tag[3] = 0;
}
