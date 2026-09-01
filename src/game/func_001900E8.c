extern int D_001E4BC4[];
struct Device { char pad[0x24]; int ready; };
extern struct Device D_002DEBC0;
extern int D_002DEC40[];
extern int D_002E0180[];
extern int func_001987F0(int handle);
extern void func_001987C0(int handle);
extern int func_0019B760(char *name, int a, int b, void *in, int inlen, void *out, int outlen, int g, int h);

int func_001900E8(int argument) {
    int status;
    if (func_001987F0(D_001E4BC4[0]) < 0) {
        return -0xC8;
    }
    if (D_002DEBC0.ready == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -0x64;
    }
    D_002DEC40[1] = argument;
    status = func_0019B760((char *)&D_002DEBC0, 0x15, 0, D_002DEC40, 0x30, D_002E0180, 4, 0, 0);
    if (status != 0) {
        func_001987C0(D_001E4BC4[0]);
        return status;
    }
    func_001987C0(D_001E4BC4[0]);
    return D_002E0180[0];
}
