extern int D_001ED0C0;
extern int D_001ED0C4;

void func_00108130(int index, int value) {
    int off;

    if (index == -1) {
        if (D_001ED0C4 > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED0C0) = value;
                index++;
                off += 0xB70;
            } while (index < D_001ED0C4);
        }
        return;
    }
    *(int *)(index * 0xB70 + D_001ED0C0) = value;
}
