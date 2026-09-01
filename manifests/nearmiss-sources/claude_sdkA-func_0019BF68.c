typedef struct { int unk0, unk4, unk8, unkC; } Entry;
extern Entry D_002E3A00[];
extern int D_001E5B88[];
extern void func_0019BE80(void);
extern void func_001987E0(int semaphore);
extern void func_001987C0(int semaphore);

Entry *func_0019BF68(int index) {
    Entry *entry;

    func_0019BE80();
    func_001987E0(D_001E5B88[0]);
    if ((unsigned int)index >= 0x20) {
        func_001987C0(D_001E5B88[0]);
        return 0;
    }
    entry = &D_002E3A00[index];
    func_001987C0(D_001E5B88[0]);
    return entry;
}
