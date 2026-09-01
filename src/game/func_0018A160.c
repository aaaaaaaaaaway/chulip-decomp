struct Payload { char data[12]; };
struct Command { int command; int f4; int f8; struct Payload payload; int f18; int result; };
extern struct Command D_002DE880;
extern char D_002DE640[];
extern int func_0019B760(char *name, int a, int b, void *in, int inlen, void *out, int outlen, int g, int h);
extern void func_00189830(int a, int b, int c);

int func_0018A160(int a, int b, struct Payload *payload) {
    int result;
    D_002DE880.f4 = a;
    D_002DE880.command = 0xB;
    D_002DE880.f8 = b;
    D_002DE880.payload = *payload;
    if (func_0019B760(D_002DE640, 1, 0, &D_002DE880, 0x80, &D_002DE880, 0x80, 0, 0) < 0) {
        return 0;
    }
    result = D_002DE880.result;
    if (result == 1) {
        func_00189830(a, b, 2);
        result = D_002DE880.result;
    }
    return result;
}
