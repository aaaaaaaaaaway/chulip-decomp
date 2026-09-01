typedef struct Rec {
    int a;
    int b;
    int c;
    int scale;
    int extra;
    unsigned char pad[0x18];
} Rec;

extern Rec *D_001ED880;

void func_0017CAF8(int handle, int a, int b, int c, int d, int e, int f);

void func_001793C0(int handle, int index, int value, int flag) {
    Rec *rec = D_001ED880 + index;

    func_0017CAF8(handle | 0x10000000, rec->a, rec->b, rec->c,
                  (rec->scale * value) / 128, rec->extra, flag);
}
