typedef struct { int unk0; int unk4; int unk8; int unkC; } Entry;

extern Entry D_002E3A00[];
extern int D_001E5B80[];
extern int D_001E5B88[];

extern int func_0019C3E8(int lock);
extern void func_0019C418(void);
extern int func_0019C4E8(void);
extern Entry *func_0019BEE0(void);
extern int func_0019D818(int arg, int rpc);
extern int func_001987C0(int sema);
extern int func_001987E0(int sema);

int func_0019DF60(int arg) {
    Entry *e;
    int r;

    func_0019C3E8(9);
    if (D_001E5B80[0] == 0) {
        func_0019C4E8();
    }
    func_0019C418();
    e = func_0019BEE0();
    if (e == 0) {
        return -19;
    }
    r = func_0019D818(arg, 9);
    if (r < 0) {
        func_001987E0(D_001E5B88[0]);
        e->unk4 = 0;
        goto out;
    }
    func_001987E0(D_001E5B88[0]);
    e->unk0 = r;
    r = e - D_002E3A00;
out:
    func_001987C0(D_001E5B88[0]);
    return r;
}
