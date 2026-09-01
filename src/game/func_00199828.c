typedef struct {
    int unk0;
    int head;
    unsigned char entries[512][2];
} Queue;

extern Queue D_002E05C8[];
extern int D_002E05C0[];
extern int D_001E5AE8[];
extern void func_001987D0(int semaphore);

int func_00199828(unsigned int value) {
    int index;

    if (value >= 0x80) {
        return -1;
    }
    if (D_001E5AE8[0] == 0) {
        return -1;
    }
    index = D_002E05C8->head & 0x1FF;
    D_002E05C8->head = index + 1;
    D_002E05C8->entries[index][0] = 1;
    D_002E05C8->entries[index][1] = value;
    func_001987D0(D_002E05C0[0]);
    return value;
}
