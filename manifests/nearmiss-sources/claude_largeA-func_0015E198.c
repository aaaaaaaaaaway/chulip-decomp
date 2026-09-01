typedef struct {
    char text[0x200];
    char lines[3][0x40];
    int unk2C0;
    int unk2C4[3];
    int unk2D0[3];
    int pad2DC[3];
    float unk2E8;
    float unk2EC;
    short unk2F0;
    short unk2F2;
    short unk2F4;
    short unk2F6;
    int pad2F8[3];
    int unk304;
    int unk308;
    int unk30C;
    int unk310;
    int unk314;
    int unk318;
    int unk31C;
    int pad320[2];
    int unk328;
    int unk32C;
    int pad330[6];
} Message;

extern Message D_002D78C0[];
extern char D_001ECD18[];
extern char D_001ECD20[];

extern void func_001923F4(void *, int, int);
extern void func_0015DED8(char *, char *);
extern char *func_0015DD70(char *, char *);
extern void func_0015DD38(int);
extern int func_0015EB88(void);
extern void func_0015F0F0(char *, char *);
extern void func_00127270(short, short);
extern void func_001272A8(float, float);
extern int func_00127A88(char *);
extern int func_00127C30(char *);

void func_0015E198(int slot, char *src, int arg2) {
    char *p;
    char *q;
    char *t;
    int total;
    int i;

    func_001923F4((D_002D78C0 + slot)->text, 0, 0x200);
    func_0015DED8((D_002D78C0 + slot)->text, src);
    t = func_0015DD70((D_002D78C0 + slot)->text, D_001ECD18);
    if (t != 0) {
        t[1] = 0;
        t[0] = 0;
    }
    p = (D_002D78C0 + slot)->text;
    total = 0;
    while (*p != 0) {
        total += *p;
        p++;
    }
    func_0015DD38(total);
    (D_002D78C0 + slot)->unk32C = total;
    (D_002D78C0 + slot)->unk328 = total;
    (D_002D78C0 + slot)->unk310 = arg2;
    (D_002D78C0 + slot)->unk2C0 = 0;
    (D_002D78C0 + slot)->unk308 = 0;
    (D_002D78C0 + slot)->unk30C = 0;
    (D_002D78C0 + slot)->unk314 = 0;
    (D_002D78C0 + slot)->unk31C = 0;
    (D_002D78C0 + slot)->unk318 = func_0015EB88();
    (D_002D78C0 + slot)->unk304 = 1;
    p = (D_002D78C0 + slot)->lines[0];
    for (i = 0; i < 3; i++) {
        func_001923F4(p, 0, 0x40);
        p[0] = 0;
        p[1] = 0;
        p += 0x40;
    }
    q = src;
    p = (D_002D78C0 + slot)->lines[0];
    for (i = 0; i < 3; i++) {
        func_0015F0F0(p, q);
        t = func_0015DD70(p, D_001ECD20);
        if (t == 0) {
            break;
        }
        t[1] = 0;
        t[0] = 0;
        q = func_0015DD70(q, D_001ECD20) + 2;
        p += 0x40;
    }
    func_00127270((D_002D78C0 + slot)->unk2F0, (D_002D78C0 + slot)->unk2F4);
    func_001272A8((D_002D78C0 + slot)->unk2E8, (D_002D78C0 + slot)->unk2EC);
    for (i = 0; i < 3; i++) {
        p = (D_002D78C0 + slot)->lines[i];
        if (p[0] == 0 && p[1] == 0) {
            D_002D78C0[slot].unk2C4[i] = 0;
            D_002D78C0[slot].unk2D0[i] = 0;
        } else {
            D_002D78C0[slot].unk2C4[i] = func_00127A88(p);
            D_002D78C0[slot].unk2D0[i] = func_00127C30(p);
        }
    }
}
