struct Entry20 { unsigned short id; char pad_0x2[0x1E]; };

struct Rec40C {
    int count;
    char pad_0x4[0x14];
    struct Entry20 entries[31];
};

extern struct Rec40C *func_0014D860(unsigned short index);
extern void func_00158BB8(unsigned short id, unsigned char arg1);

void func_0014B9A0(unsigned char index, unsigned char arg1) {
    struct Rec40C *rec = func_0014D860(index);
    unsigned int i;

    for (i = 0; i < rec->count; i++) {
        func_00158BB8(rec->entries[i].id, arg1);
    }
}
