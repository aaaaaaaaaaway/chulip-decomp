struct Entry_001FA200 {
    int kind;
    int field_0x4;
    int field_0x8;
    int field_0xC;
};

extern int D_001ED1FC;
extern int D_001ED200;
extern struct Entry_001FA200 D_001FA200[];

extern void func_00119B78(void);
extern int func_00113228(unsigned char *out, int count);
extern int func_00119D98(unsigned char *out, int index, int arg);
extern int func_00119FA0(unsigned char *out, int index, int arg);
extern int func_0011A198(unsigned char *out, int index, int arg);
extern int func_0011A3D8(unsigned char *out, int index, int arg);
extern int func_0011A5F0(unsigned char *out, int index, int arg);
extern int func_0011A820(unsigned char *out, int index, int arg);

int func_00119BB8(unsigned char *out, int unused, int arg) {
    unsigned char *head;
    int written;
    int total;
    int i;
    int kind;

    if (D_001ED1FC != 0) {
        return 0;
    }
    if (D_001ED200 == 0) {
        return 0;
    }
    func_00119B78();
    head = out;
    out += 16;
    head[3] = 0x10;
    written = 0;
    total = func_00113228(out, 9);
    out += total * 16;
    *(long *)(out + 0) = 0x1000000000008001;
    *(long *)(out + 8) = 0xE;
    *(long *)(out + 24) = 0x42;
    *(long *)(out + 16) = 0x8000000044;
    total += 2;
    out += 32;
    for (i = 0; i < 20; i++) {
        kind = D_001FA200[i].kind;
        if (kind != -1) {
            switch (kind) {
            case 1:
                written = func_00119D98(out, i, arg);
                break;
            case 2:
                written = func_00119FA0(out, i, arg);
                break;
            case 3:
                written = func_0011A198(out, i, arg);
                break;
            case 4:
                written = func_0011A3D8(out, i, arg);
                break;
            case 5:
                written = func_0011A5F0(out, i, arg);
                break;
            case 6:
                written = func_0011A820(out, i, arg);
                break;
            }
            total += written;
            out += written * 16;
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
