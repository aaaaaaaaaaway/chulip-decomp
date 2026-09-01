typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
} Entry;
extern Entry D_002E3A00[];
extern int D_001E5B88[];
extern void func_0019BE80(void);
extern volatile unsigned int func_001987E0(int semaphore);
extern void func_001987C0(int semaphore);
Entry *func_0019BEE0(void) {
    Entry *entry;
    func_0019BE80();
    func_001987E0(D_001E5B88[0]);
    for (entry = D_002E3A00; entry < (D_002E3A00 + 0x20); entry++) {
        if (entry->unk4 == 0) {
            entry->unk4 = 0x10000000;
            func_001987C0(D_001E5B88[0]);
            return entry;
        }
    }

    func_001987C0(D_001E5B88[0]);
    return 0;
}
