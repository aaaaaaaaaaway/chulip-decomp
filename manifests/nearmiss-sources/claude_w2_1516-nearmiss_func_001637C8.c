typedef struct Buffer {
    unsigned char pad[0x14];
    unsigned short f14;
} Buffer;

extern void *D_001ECD80;
extern void *D_001ECDC0;
extern void *D_001ECE00;
extern void *D_001ED680;
extern void *D_001ED6C0;
extern Buffer *D_001ED700;
extern void *D_001ED740;
extern void *D_001ED750;
extern void *D_001ED844;
extern void *D_002D8840;
extern void *D_002D8888;
extern unsigned char D_002D89C0[];

void *func_00151A00(int size);
void *func_00163BC8(void);
void func_00163A58(void);
void func_001923F4(void *dst, int value, int size);

void func_001637C8(void) {
    D_001ECE00 = func_00151A00(0xC000);
    D_001ECD80 = func_00151A00(0x30000);
    D_001ECDC0 = func_00151A00(0x54000);
    D_001ED6C0 = func_00151A00(0x14400);
    D_001ED680 = func_00151A00(0x14400);
    D_001ED750 = func_00151A00(0x200);
    D_002D8840 = func_00151A00(0x3600);
    D_002D8888 = func_00151A00(0x2200);
    D_001ED700 = func_00151A00(0x200);
    D_001ED740 = func_00163BC8();
    func_00163A58();
    D_001ED844 = func_00151A00(0x1000);
    func_001923F4(D_002D89C0, 0, 0x20);
    D_001ED700->f14 = 2;
}
