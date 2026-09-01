typedef struct {
    unsigned char unk000;
    unsigned char pad001[0x2DB];
    int unk2DC;
    int unk2E0;
    int unk2E4;
    float unk2E8;
    float unk2EC;
    int unk2F0;
    int unk2F4;
    int unk2F8;
    int unk2FC;
    int unk300;
    int unk304;
    int unk308;
    int unk30C;
    int unk310;
    int unk314;
    int unk318;
    int unk31C;
    int unk320;
    int unk324;
    int unk328;
    int unk32C;
    int unk330;
    int unk334;
    int unk338;
    int unk33C;
    int unk340;
    int unk344;
} Dialog;

struct S8Ptr {
    int a;
    int b;
};

extern Dialog D_002D78C0[];
extern int D_001ECD00;
extern struct S8Ptr D_001ECD04;

extern void func_001261F8(void);
extern void func_00127270(int, int);
extern int func_00151A00(int);

void func_0015DFC0(void) {
    int i;
    Dialog *dialog;

    func_001261F8();
    func_00127270(0, 1);
    if (D_001ECD00 == 0) {
        D_001ECD00 = func_00151A00(0x20000);
        D_001ECD04.a = func_00151A00(0x20000);
    }
    dialog = D_002D78C0;
    for (i = 0; i < 2; i++) {
        dialog->unk000 = 0;
        dialog->unk2DC = 0x800;
        dialog->unk2E0 = 0x800;
        dialog->unk2E4 = 0;
        dialog->unk2E8 = 1.0f;
        dialog->unk2EC = 0.5f;
        dialog->unk2F0 = 1;
        dialog->unk2F4 = 0;
        dialog->unk2F8 = 0;
        dialog->unk2FC = 1;
        dialog->unk300 = 0;
        dialog->unk304 = 0;
        dialog->unk308 = 0;
        dialog->unk30C = 0;
        dialog->unk310 = 0;
        dialog->unk314 = 0;
        dialog->unk318 = 0;
        dialog->unk31C = -1;
        dialog->unk324 = 0;
        dialog->unk328 = 0;
        dialog->unk32C = 0;
        dialog->unk330 = 0x20000010 + i;
        dialog->unk334 = 0;
        dialog->unk338 = 0;
        dialog->unk340 = 0xC;
        dialog->unk33C = 5;
        dialog->unk344 = 0;
        dialog++;
    }
}
