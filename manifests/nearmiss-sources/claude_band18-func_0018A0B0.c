extern char D_002DE690[];
extern int func_00189FA0(int slot, int index, int arg);

int func_0018A0B0(int slot, int index) {
    char *entry = &D_002DE690[index * 0x1C + slot * 0x70];

    if (*(int *)(entry + 0x10) != 0) {
        return func_00189FA0(slot, index, 0xFFF);
    }
    return 0;
}
