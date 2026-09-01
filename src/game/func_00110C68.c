extern int D_001ED17C;
extern int D_001ED180;

void func_00110C68(int index, int value) {
    int off;

    if (index == -1) {
        if (D_001ED180 > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED17C) = value;
                index++;
                off += 0x1320;
            } while (index < D_001ED180);
        }
        return;
    }
    *(int *)(index * 0x1320 + D_001ED17C) = value;
}
