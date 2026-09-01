extern int D_001ED144;
extern int D_001ED148;

void func_0010D420(int index, int value) {
    int off;

    if (index == -1) {
        if (D_001ED148 > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED144) = value;
                index++;
                off += 0x660;
            } while (index < D_001ED148);
        }
        return;
    }
    *(int *)(index * 0x660 + D_001ED144) = value;
}
