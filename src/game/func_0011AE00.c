struct Qword {
    long lo;
    long hi;
};

struct Header {
    short count;
    unsigned char field_0x2;
    unsigned char field_0x3;
    unsigned char field_0x4[0xC];
};

extern int D_001ED1F8;
union Sel_001ED204 { int value; };
extern union Sel_001ED204 D_001ED204;
extern int D_001ED20C;

extern int func_00113228(struct Qword *out, int count);
extern void func_00179360(int a, int b, int c);
extern int func_0011B020(struct Qword *out, int arg);
extern int func_0011BB90(struct Qword *out, int arg);
extern int func_0011C740(struct Qword *out, int arg);
extern int func_0011CE70(struct Qword *out, int arg);
extern int func_0011DBF0(struct Qword *out, int arg);

int func_0011AE00(struct Header *buf, int arg) {
    struct Qword *out;
    int written;
    int total;

    buf->field_0x3 = 0x10;
    out = (struct Qword *)(buf + 1);
    written = func_00113228(out, 9);
    out += written;
    out[0].lo = 0x1000000000008001;
    out[0].hi = 0xE;
    out[1].hi = 0x42;
    out[1].lo = 0x8000000048;
    total = written + 2;
    out += 2;
    switch (D_001ED204.value) {
    case 0:
        if (D_001ED1F8 == 0) {
            D_001ED1F8 = 1;
            func_00179360(0x1000, 0x27, 0x7F);
        }
        written = func_0011B020(out, arg);
        break;
    case 1:
        if (D_001ED1F8 == 0) {
            D_001ED1F8 = 1;
            func_00179360(0x1000, 0, 0x7F);
        }
        written = func_0011BB90(out, arg);
        break;
    case 2:
        if (D_001ED1F8 == 0) {
            D_001ED1F8 = 1;
            func_00179360(0x1000, 0x24, 0x7F);
        }
        written = func_0011C740(out, arg);
        break;
    case 3:
        if (D_001ED1F8 == 0) {
            D_001ED1F8 = 1;
            func_00179360(0x1000, 0x25, 0x7F);
        }
        written = func_0011CE70(out, arg);
        break;
    case 4:
        if (D_001ED1F8 == 0) {
            D_001ED1F8 = 1;
            func_00179360(0x1000, 0x15, 0x7F);
        }
        written = func_0011DBF0(out, arg);
        break;
    case 5:
        break;
    }
    D_001ED20C = D_001ED20C + 1;
    total += written;
    buf->count = total;
    return total + 1;
}
