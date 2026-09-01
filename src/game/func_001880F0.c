typedef struct {
    long unk0;
    long unk8;
    long unk10;
    long unk18;
    long unk20;
} GsRegs;

typedef struct {
    char pad0[6];
    short mode;
} DisplayInfo;

extern DisplayInfo *func_00187498(void);

#define GS_PMODE    (*(volatile long *)0x12000000)
#define GS_SMODE2   (*(volatile long *)0x12000020)
#define GS_DISPFB1  (*(volatile long *)0x12000070)
#define GS_DISPLAY1 (*(volatile long *)0x12000080)
#define GS_DISPFB2  (*(volatile long *)0x12000090)
#define GS_DISPLAY2 (*(volatile long *)0x120000A0)
#define GS_BGCOLOR1 (*(volatile long *)0x120000C0)
#define GS_BGCOLOR2 (*(volatile long *)0x120000E0)

void func_001880F0(GsRegs *regs) {
    if (func_00187498()->mode == 1) {
        GS_PMODE = regs->unk0;
        GS_DISPFB1 = regs->unk10;
        GS_DISPLAY1 = regs->unk18;
        GS_BGCOLOR1 = regs->unk20;
    } else {
        GS_PMODE = regs->unk0;
        GS_SMODE2 = regs->unk8;
        GS_DISPFB2 = regs->unk10;
        GS_DISPLAY2 = regs->unk18;
        GS_BGCOLOR2 = regs->unk20;
    }
}
