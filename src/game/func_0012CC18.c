struct Actor_001ED310 {
    unsigned char field_0x00[0x20];
    unsigned char field_0x20[0x40];
    unsigned char field_0x60;
    unsigned char field_0x61;
    unsigned short field_0x62;
    unsigned short field_0x64;
    unsigned short field_0x66;
    unsigned short field_0x68;
    unsigned short field_0x6A;
    int field_0x6C;
    unsigned char field_0x70[0x8];
    short field_0x78;
    short field_0x7A;
    int field_0x7C;
};

struct Session_00136AE8 {
    unsigned char field_0x00[0x42];
    unsigned char field_0x42;
};

extern struct Actor_001ED310 *D_001ED310;
extern struct Session_00136AE8 *func_00136AE8(void);
extern int func_00192940(void *destination, void *source);
extern int func_0015DE90(void *destination, void *source);

int func_0012CC18(int index, unsigned char field, void *buffer) {
    struct Session_00136AE8 *session = func_00136AE8();

    switch (field) {
    case 3:
        return (D_001ED310 + index)->field_0x60;
    case 4:
        if (session->field_0x42 == 2) {
            return (D_001ED310 + index)->field_0x62 | -0x11;
        }
        return (D_001ED310 + index)->field_0x62;
    case 1:
        func_00192940(buffer, (D_001ED310 + index)->field_0x20);
        return 1;
    case 0:
        func_0015DE90(buffer, D_001ED310 + index);
        return 1;
    case 7:
        if (index > 0x80) {
            return 0x43A;
        }
        return (D_001ED310 + index)->field_0x66;
    case 8:
        return (D_001ED310 + index)->field_0x68 + 0x2C0;
    case 9:
        return (D_001ED310 + index)->field_0x6C;
    case 10:
        return ((D_001ED310 + index)->field_0x62 >> 4) & 1;
    case 11:
        return (D_001ED310 + index)->field_0x78;
    case 12:
        return (((D_001ED310 + index)->field_0x62 >> 2) ^ 1) & 1;
    }
    return 0;
}
