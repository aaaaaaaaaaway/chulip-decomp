struct Vec16_001369C8 { int field_0x0; int field_0x4; int field_0x8; int field_0xC; };

extern int D_001ED370;
extern int D_001ED374;
extern int D_001ED378;
extern struct Vec16_001369C8 D_001A77B0;
extern struct Vec16_001369C8 D_001A77F0;
extern struct Vec16_001369C8 D_001A7D30;
extern struct Vec16_001369C8 D_001A7790;

extern void func_00135BD8(int a, int b, struct Vec16_001369C8 *value);
extern void func_0018A680(struct Vec16_001369C8 *dst, struct Vec16_001369C8 *src);
extern void func_00128378(struct Vec16_001369C8 *dst, struct Vec16_001369C8 *a, struct Vec16_001369C8 *b);
extern void func_0014D7A8(struct Vec16_001369C8 *value);
extern void func_00136AF8(unsigned char kind, unsigned char value);

void func_001369C8(void) {
    struct Vec16_001369C8 matrix;

    D_001ED378 = 1;
    D_001ED374 = 2;
    D_001ED370 = 0;
    func_00135BD8(0, 0, &D_001A77B0);
    func_00135BD8(D_001ED370, 1, &D_001A77F0);
    func_00135BD8(D_001ED370, 2, &D_001A77F0);
    func_0018A680(&D_001A7790, &D_001A7D30);
    func_00128378(&matrix, &D_001A77B0, &D_001A7D30);
    func_0014D7A8(&matrix);
    func_00136AF8(0, 1);
}
