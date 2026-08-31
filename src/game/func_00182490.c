typedef struct {
    unsigned char value;
    unsigned char pad[7];
} Flag8;

extern Flag8 D_001ED9B8;
extern int D_001ED9B4;
extern int D_002DB640[];

extern int func_00128F58(int index);
extern int func_00128E10(int index);
extern int func_00128FB8(int index);
extern int func_00182210(char *dst, long a, long b);
extern int func_001825A8(char *dst);
extern int func_00184918(char *dst, int *state);
extern int func_001827E8(char *dst, int *state);
extern int func_00182B70(char *dst, int *state);

int func_00182490(char *buffer) {
    char *p = buffer;
    int mode;

    D_002DB640[35] = func_00128F58(D_001ED9B8.value);
    D_002DB640[36] = func_00128E10(D_001ED9B8.value);
    D_001ED9B4 = func_00128FB8(D_001ED9B8.value);
    p += func_00182210(p, 0x47, 0x71001) * 16;
    p += func_001825A8(p) * 16;
    p += func_00184918(p, D_002DB640) * 16;
    mode = D_002DB640[1];
    if (mode == 1 || mode == 3 || mode == 2) {
        p += func_001827E8(p, D_002DB640) * 16;
        p += func_00182B70(p, D_002DB640) * 16;
    }
    return (int)(p - buffer) / 16;
}
