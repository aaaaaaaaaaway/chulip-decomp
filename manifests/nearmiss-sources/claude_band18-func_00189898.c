extern char D_002DE690[];
extern char *func_00189650(int slot);

int func_00189898(int slot, int index) {
    char *entry = &D_002DE690[index * 0x1C + slot * 0x70];
    int result = 0;

    if (*(int *)(entry + 0x10) != 0) {
        result = *(unsigned char *)(func_00189650(slot) + 0x71);
    }
    return result;
}
