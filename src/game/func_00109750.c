extern int D_001ED0E0;
extern int D_001ED0E4;

void func_00109750(int index, int value) {
    int off;

    if (index == -1) {
        if (D_001ED0E4 > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED0E0) = value;
                index++;
                off += 0x1F0;
            } while (index < D_001ED0E4);
        }
        return;
    }
    *(int *)(index * 0x1F0 + D_001ED0E0) = value;
}
