extern int D_001ED0D4;
extern int D_001ED0D8;

void func_00109138(int index, int value) {
    int off;

    if (index == -1) {
        if (D_001ED0D8 > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED0D4) = value;
                index++;
                off += 0x70;
            } while (index < D_001ED0D8);
        }
        return;
    }
    *(int *)(index * 0x70 + D_001ED0D4) = value;
}
