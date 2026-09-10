typedef struct {
    unsigned char metadata[0x28];
    int pixels;
    unsigned short unknown2c;
    unsigned short resource;
    unsigned short storage;
    unsigned short unknown32;
} Surface;
extern Surface *D_001ED940;
extern char D_001EAB98[];
extern char D_001EABA8[];
unsigned char *func_00137F98(void);
char *func_00192940(char *destination, const char *source);
char *func_001926D0(char *destination, const char *source);
void func_00137F10(int index, int *out);
int func_00137F28(int index);
void func_00137EE0(int index, int *out);
int func_00137EF8(int index);
void func_00137F68(int index, int *out);
int func_00137F80(int index);
int func_00125CD8(char *path, int *out, unsigned short resource);

int func_0017E1A0(int id, int unused_offset, int unused_size) {
    char path[32];
    if (id & 0x1000) {
        func_00192940(path, (char *)func_00137F98());
        func_001926D0(path, D_001EAB98);
        switch (D_001ED940->storage) {
        case 0:
            func_00137F10(D_001ED940->resource, &D_001ED940->pixels);
            return func_00137F28(D_001ED940->resource);
        case 1:
            func_00137EE0(D_001ED940->resource, &D_001ED940->pixels);
            return func_00137EF8(D_001ED940->resource);
        case 2:
            return 0;
        default:
            return func_00125CD8(path, &D_001ED940->pixels, D_001ED940->resource);
        }
    } else {
        switch (D_001ED940->storage) {
        case 0:
            func_00137F10(D_001ED940->resource, &D_001ED940->pixels);
            return func_00137F28(D_001ED940->resource);
        case 1:
            func_00137EE0(D_001ED940->resource, &D_001ED940->pixels);
            return func_00137EF8(D_001ED940->resource);
        case 2:
            func_00137F68(D_001ED940->resource, &D_001ED940->pixels);
            return func_00137F80(D_001ED940->resource);
        default:
            return func_00125CD8(D_001EABA8, &D_001ED940->pixels, D_001ED940->resource);
        }
    }
}
