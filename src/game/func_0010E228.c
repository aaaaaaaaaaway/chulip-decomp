extern char *D_001ED150[];

void func_0010E228(int value) {
    int offset = 0;
    int i = 7;

    do {
        *(int *)(D_001ED150[0] + offset + 0x30) = value;
        offset += 0x660;
    } while (--i >= 0);
}
