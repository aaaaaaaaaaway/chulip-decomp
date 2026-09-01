extern char D_002DEBC0[];
extern char D_002DEC40[];
extern char D_001EBBF0[];
extern int D_002E0180[];
extern int func_0019B760(char *name, int a, int b, void *in, int inlen, void *out, int outlen, int g, int h);
extern void func_00192508(char *message);

int func_00190B08(void) {
    if (func_0019B760(D_002DEBC0, 0x35, 0, D_002DEC40, 0x30, D_002E0180, 4, 0, 0) != 0) {
        func_00192508(D_001EBBF0);
        return -1;
    }
    return D_002E0180[0];
}
