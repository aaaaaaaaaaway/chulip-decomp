extern int D_001ED11C;
extern int D_001ED120;

void func_0010BC18(int index, int value) {
    int off;

    if (index == -1) {
        if (D_001ED120 > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED11C) = value;
                index++;
                off += 0x70;
            } while (index < D_001ED120);
        }
        return;
    }
    *(int *)(index * 0x70 + D_001ED11C) = value;
}
