extern char D_002DB640[];
extern int func_00182210(char *dst, long a, long b);
extern int func_00185218(char *dst, char *src);
extern int func_001825A8(char *dst);

int func_00182410(char *buffer) {
    char *p = buffer;

    p += func_00182210(p, 0x47, 0x31001) * 16;
    p += func_00185218(p, D_002DB640) * 16;
    p += func_001825A8(p) * 16;
    return (int)(p - buffer) / 16;
}
