typedef struct EventRecord {
    unsigned int key;
    unsigned int flags;
    short current_ticks;
    short initial_ticks;
    short elapsed;
    short delay;
    unsigned int state;
    unsigned short values[4];
    int next;
    int previous;
} EventRecord;
extern EventRecord D_00203C20[];

unsigned short *func_00138DF0(int index) {
    return D_00203C20[index].values;
}
