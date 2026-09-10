typedef unsigned short u16;
typedef struct {
    u16 sequence;
    u16 event;
    u16 first_time;
    u16 second_time;
    u16 first_frame;
    u16 second_frame;
} AnimationEvents;
extern AnimationEvents D_002D48C0[];
extern int func_00154560(u16 index);
extern void func_00138E58(int key, short *values, unsigned int field);
extern int func_00138CC8(int key, short *values, int field);
extern int func_00138468(unsigned int key, int time, unsigned int flags, u16 *values);

void func_0015D410(int index, int sequence) {
    u16 times[2];
    short values[4];
    int event;
    if (index == 0) {
        switch (sequence) {
        case 2:
            values[0] = 16;
            times[0] = 8;
            times[1] = 24;
            break;
        case 18:
            values[0] = 16;
            times[0] = 10;
            times[1] = 25;
            break;
        case 17:
            values[1] = 0;
            func_00138E58(0x49, values, 2);
            return;
        default:
            values[0] = -1;
            break;
        }
        if (values[0] == -1)
            return;
        values[0] = -1;
        values[1] = 0;
        func_00138E58(0x49, values, 2);
        if (times[0] != 0xFFFF) {
            values[2] = sequence;
            values[3] = 1;
            func_00138468(0x49, times[0], 2, (u16 *)values);
        }
        if (times[1] != 0xFFFF) {
            values[2] = sequence;
            values[3] = 1;
            func_00138468(0x49, times[1], 2, (u16 *)values);
        }
    } else {
        if (sequence != D_002D48C0[index].sequence)
            return;
        values[1] = index;
        if (!func_00154560(index))
            return;
        event = func_00138CC8(0x13, values, 2);
        if (event != -1)
            return;
        if (D_002D48C0[index].event == 0xFFFF) {
            if (D_002D48C0[index].first_time != 0xFFFF) {
                values[0] = event;
                values[1] = index;
                values[2] = D_002D48C0[index].sequence;
                values[3] = 1;
                func_00138468(0x49, D_002D48C0[index].first_time, 2, (u16 *)values);
            }
            if (D_002D48C0[index].second_time != 0xFFFF) {
                values[0] = event;
                values[1] = index;
                values[2] = D_002D48C0[index].sequence;
                values[3] = 1;
                func_00138468(0x49, D_002D48C0[index].second_time, 2, (u16 *)values);
            }
        } else {
            event = D_002D48C0[index].event;
            if (D_002D48C0[index].first_time != 0xFFFF) {
                values[0] = event;
                values[1] = index;
                values[2] = D_002D48C0[index].sequence;
                values[3] = 1;
                func_00138468(0x48, D_002D48C0[index].first_time, 2, (u16 *)values);
            }
            if (D_002D48C0[index].second_time != 0xFFFF) {
                values[0] = event;
                values[1] = index;
                values[2] = D_002D48C0[index].sequence;
                values[3] = 1;
                func_00138468(0x48, D_002D48C0[index].second_time, 2, (u16 *)values);
            }
        }
    }
}
