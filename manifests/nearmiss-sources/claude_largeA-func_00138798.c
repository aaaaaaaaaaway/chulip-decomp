typedef struct {
    unsigned int unk00;
    int flags;
    int pad08[2];
    int unk10;
    unsigned char unk14;
    unsigned char pad15;
    unsigned char unk16;
    unsigned char pad17;
    unsigned char unk18;
    unsigned char pad19;
    unsigned char unk1A;
    unsigned char pad1B;
    int prev;
    int next;
} SoundNode;

extern SoundNode D_00203C20[];
extern int D_00203C00[];
extern void func_001392C0(int);

void func_00138798(int index) {
    if (D_00203C20[index].next != -1) {
        D_00203C20[D_00203C20[index].next].prev = D_00203C20[index].prev;
    }
    if (D_00203C20[index].prev != -1) {
        D_00203C20[D_00203C20[index].prev].next = D_00203C20[index].next;
    }
    if (index == D_00203C00[2]) {
        D_00203C00[2] = D_00203C20[index].prev;
    }
    if (index == D_00203C00[3]) {
        D_00203C00[3] = D_00203C20[index].next;
        if (D_00203C20[index].next == -1) {
            D_00203C00[2] = D_00203C20[index].next;
        }
    }
    D_00203C20[index].unk00 = 0xFFFFFFFF;
    D_00203C20[index].unk10 &= ~2;
    if ((D_00203C20[index].flags & 0x20) != 0) {
        func_001392C0(D_00203C20[index].unk14);
    }
    if ((D_00203C20[index].flags & 0x40) != 0) {
        func_001392C0(D_00203C20[index].unk16);
    }
    if ((D_00203C20[index].flags & 0x80) != 0) {
        func_001392C0(D_00203C20[index].unk18);
    }
    if ((D_00203C20[index].flags & 0x100) != 0) {
        func_001392C0(D_00203C20[index].unk1A);
    }
    D_00203C20[index].flags = 0;
}
