extern int D_001ED0EC;
extern int D_001ED0F0;

void func_00109CC8(int index, int value) {
    int off;

    if (index == -1) {
        if (D_001ED0F0 > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED0EC) = value;
                index++;
                off += 0x70;
            } while (index < D_001ED0F0);
        }
        return;
    }
    *(int *)(index * 0x70 + D_001ED0EC) = value;
}
