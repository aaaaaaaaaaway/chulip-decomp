extern int D_001E30A8[];
extern unsigned char D_001EB0E8[];
extern void func_00192940(unsigned char *out, int value);

void func_001897F8(unsigned int index, unsigned char *out) {
    if (index < 8) {
        func_00192940(out, D_001E30A8[index]);
        return;
    }
    *out = D_001EB0E8[0];
}
