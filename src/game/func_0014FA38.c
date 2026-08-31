struct Rec40 {
    char pad_0x0[0x10];
    unsigned int field_0x10;
    char pad_0x14[0x2C];
};

extern char D_001A88C8[];
extern char D_001ECB58[];
extern char D_001ECB68[];
extern struct Rec40 D_00286440[];

extern void func_00192660(char *dst, char *fmt, char *arg);
extern void func_00190B78(int arg0, int arg1, char *arg2, int arg3, int arg4, struct Rec40 *arg5);
extern void func_00190848(int arg0, int arg1, int *out);
extern void func_00191558(int arg0, int arg1, char *arg2);

int func_0014FA38(void) {
    char path[0x100];
    int count;
    int entries;
    int total;
    int i;

    func_00192660(path, D_001ECB68, D_001A88C8);
    func_00190B78(0, 0, path, 0, 0x20, D_00286440);
    func_00190848(0, 0, &count);
    if (count < 0) {
        if (count == -4 || count == -2) {
            return 0;
        }
        return -1;
    }
    func_00192660(path, D_001ECB58, D_001A88C8);
    func_00191558(0, 0, path);
    func_00190848(0, 0, &entries);
    if (entries < 0) {
        return -1;
    }
    total = (count + entries + 1) / 2 + 1;
    for (i = 0; i < count; i++) {
        total += (D_00286440[i].field_0x10 + 0x3FF) / 1024;
    }
    return total;
}
