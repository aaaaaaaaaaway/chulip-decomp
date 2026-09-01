extern unsigned char D_002A1E80[];
extern unsigned char D_002A3080[];
extern unsigned char D_002A4280[];
extern unsigned char D_002A5480[];
extern unsigned char D_002A6680[];
extern unsigned char D_002A7880[];
extern unsigned char D_002A8A80[];
extern unsigned char D_002A9C80[];
extern unsigned char D_00288E80[];
extern unsigned char D_00294E80[];
extern int D_001ED458;
extern int D_001ED45C;

void func_001923F4(void *dst, int value, int size);
int func_001916A8(int count, int size);

void func_001512E8(void) {
    func_001923F4(D_002A5480, 0, 0x1200);
    func_001923F4(D_002A1E80, 0, 0x1200);
    func_001923F4(D_002A6680, 0, 0x1200);
    func_001923F4(D_002A7880, 0, 0x1200);
    func_001923F4(D_002A8A80, 0, 0x1200);
    func_001923F4(D_002A9C80, 0, 0x1200);
    func_001923F4(D_002A4280, 0, 0x1200);
    func_001923F4(D_002A3080, 0, 0x1200);
    func_001923F4(D_00288E80, -1, 0xC000);
    func_001923F4(D_00294E80, -1, 0xC000);
    D_001ED458 = func_001916A8(0x80, 0x1A00000);
    D_001ED45C = 0;
}
