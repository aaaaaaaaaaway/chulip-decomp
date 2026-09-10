/* Remove an existing keyed range from the index-based doubly linked list. */
typedef unsigned int u32;

struct Pair {
    u32 first;
    u32 second;
};

extern struct Pair D_00288E80[];
extern struct Pair D_00294E80[];
extern u32 D_001ECBD0;
extern u32 D_001ECBD4;
extern u32 D_001ED45C;

u32 func_001520D8(u32 key)
{
    u32 tail = D_001ECBD4;
    u32 cursor = tail;
    u32 previous, next, first, second;

    for (; cursor != 0xFFFFFFFF; cursor = D_00294E80[cursor].first) {
        if (key == D_00288E80[cursor].first) {
            break;
        }
    }
    previous = D_00294E80[cursor].first;
    next = D_00294E80[cursor].second;
    if (cursor == D_001ECBD0) {
        D_001ECBD0 = next;
        if (next != 0xFFFFFFFF) {
            D_00294E80[next].first = 0xFFFFFFFF;
        }
    } else if (cursor == tail) {
        D_001ECBD4 = previous;
        if (previous != 0xFFFFFFFF) {
            D_00294E80[previous].second = 0xFFFFFFFF;
        }
    } else {
        D_00294E80[previous].second = next;
        D_00294E80[next].first = previous;
    }
    second = D_00288E80[cursor].second;
    first = D_00288E80[cursor].first;
    D_00288E80[cursor].first = 0xFFFFFFFF;
    D_00288E80[cursor].second = 0xFFFFFFFF;
    D_00294E80[cursor].first = 0xFFFFFFFF;
    D_00294E80[cursor].second = 0xFFFFFFFF;
    D_001ED45C--;
    return second - first;
}
