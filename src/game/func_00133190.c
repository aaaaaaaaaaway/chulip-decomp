struct Header_00133190 { int field_0x0; unsigned char *field_0x4; unsigned char *field_0x8; };

extern unsigned char D_001A7780[0x10];

extern void func_0018A680(unsigned char *dst, unsigned char *src);

void func_00133190(unsigned char *dst, unsigned char *src, unsigned char *arg2) {
    struct Header_00133190 *header = (struct Header_00133190 *)dst;
    int value;

    arg2 = arg2 + 0x10;
    value = *(int *)(src + 0xC);
    src = src + 0x10;
    header->field_0x8 = arg2;
    header->field_0x4 = src;
    header->field_0x0 = value;
    func_0018A680(dst + 0x10, D_001A7780);
    func_0018A680(dst + 0x20, D_001A7780);
}
