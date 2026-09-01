struct Rec_001A5718 { unsigned short field_0x0; unsigned char field_0x2; unsigned char pad_0x3[0x2A1]; };

extern struct Rec_001A5718 D_001A5718[];

extern int func_0012D998(int id, int kind, int flag);
extern void func_0015E518(int a, int b, int c, int d, int e, int f);
extern void func_0017C9F0(int a, int b, int c);
extern void func_00173050(int a, int b);

void func_0012F700(unsigned char index) {
    struct Rec_001A5718 *record;
    int first;
    int second;

    record = D_001A5718 + index;
    if (record->field_0x2 == 0xFF) {
        return;
    }
    first = func_0012D998(record->field_0x2, 9, 0);
    second = func_0012D998(record->field_0x2, 7, 0);
    if (second == 0xFF) {
        return;
    }
    func_0015E518(1, 1, 0, 5, 6, first);
    func_0017C9F0(1, 0, second);
    func_00173050(0xE, second);
}
