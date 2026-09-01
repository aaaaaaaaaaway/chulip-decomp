extern int D_001ED188;
extern int D_001ED18C;

void func_00111450(int index, int value) {
    int off;

    if (index == -1) {
        if (D_001ED18C > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED188) = value;
                index++;
                off += 0x990;
            } while (index < D_001ED18C);
        }
        return;
    }
    *(int *)(index * 0x990 + D_001ED188) = value;
}
