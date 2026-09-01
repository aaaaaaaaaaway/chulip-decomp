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

extern void func_00109FF8(int value);
extern void func_001074A8(int value);
extern void func_0010CF80(int arg, int value);
extern void func_00107B68(int arg, int value);
extern void func_0010DC70(int value);
extern void func_00110758(int arg, int value);
extern void func_00111288(int arg, int value);
extern void func_00133960(int arg, int value);
extern void func_00106AB8(int arg, int value);
extern void func_00105C38(int arg, int value);
extern void func_00106300(int arg, int value);
extern void func_0010C7B0(int arg, int value);
extern void func_0010AA10(int arg, int value);
extern void func_0010FFF0(int value);
extern void func_0010E608(int value);
extern void func_0010F0F0(int value);
extern void func_0010BF10(int value);

void func_00178B18(unsigned short kind, unsigned short arg) {
    int i;

    i = 0;
    while (D_001ED7D0[i].field_0x1 != kind) {
        if (i >= D_001ECED0) {
            break;
        }
        i++;
    }
    switch (kind) {
    case 5:
        func_00109FF8(D_002D88C0[i].field_0x4);
        break;
    case 6:
        func_001074A8(D_002D88C0[i].field_0x4);
        break;
    case 7:
        func_0010CF80(arg, D_002D88C0[i].field_0x4);
        break;
    case 8:
        func_00107B68(arg, D_002D88C0[i].field_0x4);
        break;
    case 9:
        func_0010DC70(D_002D88C0[i].field_0x4);
        break;
    case 10:
        func_00110758(arg, D_002D88C0[i].field_0x4);
        break;
    case 11:
        func_00111288(arg, D_002D88C0[i].field_0x4);
        break;
    case 12:
        func_00133960(arg, D_002D88C0[i].field_0x4);
        break;
    case 13:
        func_00106AB8(arg, D_002D88C0[i].field_0x4);
        break;
    case 14:
        func_00105C38(arg, D_002D88C0[i].field_0x4);
        break;
    case 15:
        func_00106300(arg, D_002D88C0[i].field_0x4);
        break;
    case 16:
        func_0010C7B0(arg, D_002D88C0[i].field_0x4);
        break;
    case 17:
        func_0010AA10(arg, D_002D88C0[i].field_0x4);
        break;
    case 20:
        func_0010FFF0(D_002D88C0[i].field_0x4);
        break;
    case 21:
        func_0010E608(D_002D88C0[i].field_0x4);
        break;
    case 22:
        func_0010F0F0(D_002D88C0[i].field_0x4);
        break;
    case 23:
        func_0010BF10(D_002D88C0[i].field_0x4);
        break;
    case 3:
    case 4:
    case 18:
    case 19:
        break;
    }
}
