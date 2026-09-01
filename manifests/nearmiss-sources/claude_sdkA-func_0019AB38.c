typedef struct {
    void *unk0;
    void *unk4;
} Slot;

extern Slot *D_002E0F24[];
extern Slot *D_002E0F2C[];

void func_0019AB38(long index, void *arg0, void *arg1) {
    Slot *table;

    if (index < 0) {
        table = D_002E0F24[0];
    } else {
        table = D_002E0F2C[0];
    }
    table[index].unk0 = arg0;
    table[index].unk4 = arg1;
}
