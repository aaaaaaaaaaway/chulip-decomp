/* Entry allocation and replacement for the shared 144-slot event list. */
typedef union RecordState {
    unsigned int word;
    struct {
        unsigned int removed : 1;
        unsigned int inactive : 1;
        unsigned int other : 30;
    } bits;
} RecordState;
typedef struct Record {
    unsigned int key;
    unsigned int flags;
    short current_ticks;
    short initial_ticks;
    short elapsed;
    short delay;
    RecordState state;
    unsigned short values[4];
    int next;
    int previous;
} Record;
typedef struct List {
    int field00, field04;
    int first, last;
    unsigned char unknown10[0x10];
} List;
extern Record D_00203C20[];
extern List D_00203C00;
extern void func_001392C0(unsigned char value);
int func_00138468(unsigned int key, int time, unsigned int flags, unsigned short *values) {
    int i;
    if (flags & 0x18) {
        for (i = 0; i < 144; i++) {
            if (D_00203C20[i].key == key && !D_00203C20[i].state.bits.inactive)
                break;
        }
        if (i < 144) {
            if (flags & 8) {
                if (flags & 0x20)
                    func_001392C0((unsigned char)values[0]);
                if (flags & 0x40)
                    func_001392C0((unsigned char)values[1]);
                if (flags & 0x80)
                    func_001392C0((unsigned char)values[2]);
                if (flags & 0x100)
                    func_001392C0((unsigned char)values[3]);
                return -1;
            } else if (flags & 0x10) {
                D_00203C20[i].key = key;
                D_00203C20[i].current_ticks = time;
                D_00203C20[i].initial_ticks = time;
                D_00203C20[i].flags = flags;
                D_00203C20[i].delay = 0;
                if (values) {
                    D_00203C20[i].values[0] = values[0];
                    D_00203C20[i].values[1] = values[1];
                    D_00203C20[i].values[2] = values[2];
                    D_00203C20[i].values[3] = values[3];
                } else {
                    D_00203C20[i].values[0] = 0;
                    D_00203C20[i].values[1] = 0;
                    D_00203C20[i].values[2] = 0;
                    D_00203C20[i].values[3] = 0;
                }
                return i;
            }
        }
    }
    for (i = 0; i < 144; i++) {
        if (D_00203C20[i].key == 0xFFFFFFFF)
            break;
    }
    D_00203C20[i].key = key;
    D_00203C20[i].current_ticks = time;
    D_00203C20[i].initial_ticks = time;
    D_00203C20[i].flags = flags;
    D_00203C20[i].elapsed = 0;
    D_00203C20[i].delay = 0;
    D_00203C20[i].state.bits.removed = 0;
    if (D_00203C00.last != -1) {
        D_00203C20[i].previous = D_00203C00.last;
        D_00203C20[D_00203C00.last].next = i;
    } else {
        D_00203C00.first = i;
        D_00203C20[i].previous = D_00203C00.last;
    }
    D_00203C00.last = i;
    D_00203C20[i].next = -1;
    if (values) {
        D_00203C20[i].values[0] = values[0];
        D_00203C20[i].values[1] = values[1];
        D_00203C20[i].values[2] = values[2];
        D_00203C20[i].values[3] = values[3];
    } else {
        D_00203C20[i].values[0] = 0;
        D_00203C20[i].values[1] = 0;
        D_00203C20[i].values[2] = 0;
        D_00203C20[i].values[3] = 0;
    }
    return i;
}
