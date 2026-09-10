typedef struct {
    unsigned char metadata[0x20];
    unsigned short allocation;
    unsigned short format;
    unsigned short width, height;
    int pixels;
    unsigned short unknown2c, resource, storage, unknown32;
} Surface;

extern Surface *D_001ED940;
extern int D_001ED978;
unsigned char *func_0017D040(unsigned int);
void func_0017E528(unsigned int);
int func_00151CA8(int);

void func_0017E6C8(unsigned int id, unsigned int mode) {
    if (id == 255)
        return;
    D_001ED940 = (Surface *)func_0017D040(id);
    switch (mode) {
    case 0x41:
        if (D_001ED940->allocation != 0) {
            func_0017E528(D_001ED940->allocation);
            D_001ED940->allocation = 0;
        }
        break;
    case 0x42:
        if (D_001ED940->storage == 0xffff && D_001ED940->pixels != 0) {
            func_00151CA8(D_001ED940->pixels);
            D_001ED940->pixels = 0;
        }
        break;
    case 0x40:
        if (D_001ED940->allocation != 0) {
            func_0017E528(D_001ED940->allocation);
            D_001ED940->allocation = 0;
        }
        if (D_001ED940->storage == 0xffff && D_001ED940->pixels != 0 &&
            D_001ED940->pixels != D_001ED978)
            func_00151CA8(D_001ED940->pixels);
        D_001ED940->pixels = 0;
        break;
    }
}
