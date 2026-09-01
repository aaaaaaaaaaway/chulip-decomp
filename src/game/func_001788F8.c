struct Entry_001ED7D0 {
    unsigned char field_0x0;
    unsigned char field_0x1;
    unsigned short field_0x2;
};

struct Slot_002D88C0 {
    int field_0x0;
    int field_0x4;
};

extern short D_001ECED0;
extern struct Entry_001ED7D0 *D_001ED7D0;
extern struct Slot_002D88C0 D_002D88C0[];
extern unsigned char D_002D89C0[];

extern void func_001519F0(void);
extern void func_00109FA0(void);
extern void func_001073C8(void);
extern void func_0010CEE8(int value);
extern void func_00107A50(int value);
extern void func_0010DBF0(int value);
extern void func_001106F8(int value);
extern void func_00111228(int value);
extern void func_00133858(int value);
extern void func_001069A0(int value);
extern void func_00105B08(int value);
extern void func_00106280(int value);
extern void func_0010C730(int value);
extern void func_0010A9A8(void);
extern void func_0010FF08(int value);
extern void func_0010E508(int value);
extern void func_0010F008(int value);
extern void func_0010BE28(int value);

void func_001788F8(unsigned short kind) {
    int i;
    unsigned short value;

    for (i = 0; i < D_001ECED0; i++) {
        if (D_001ED7D0[i].field_0x1 == kind && (D_002D88C0[i].field_0x0 & 1) == 0) {
            break;
        }
    }
    D_002D89C0[kind] = 1;
    D_002D88C0[i].field_0x0 |= 1;
    value = D_001ED7D0[i].field_0x2;
    func_001519F0();
    switch (kind) {
    case 5:
        func_00109FA0();
        break;
    case 6:
        func_001073C8();
        break;
    case 7:
        func_0010CEE8(value);
        break;
    case 8:
        func_00107A50(value);
        break;
    case 9:
        func_0010DBF0(value);
        break;
    case 10:
        func_001106F8(value);
        break;
    case 11:
        func_00111228(value);
        break;
    case 12:
        func_00133858(value);
        break;
    case 13:
        func_001069A0(value);
        break;
    case 14:
        func_00105B08(value);
        break;
    case 15:
        func_00106280(value);
        break;
    case 16:
        func_0010C730(value);
        break;
    case 17:
        func_0010A9A8();
        break;
    case 20:
        func_0010FF08(value);
        break;
    case 21:
        func_0010E508(value);
        break;
    case 22:
        func_0010F008(value);
        break;
    case 23:
        func_0010BE28(value);
        break;
    case 18:
    case 19:
        break;
    }
    func_001519F0();
}
