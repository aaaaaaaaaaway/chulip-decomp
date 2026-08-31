typedef struct {
    char pad0[0x6E];
    unsigned short id;
    char pad1[0x47];
    unsigned char flag;
    char pad2[8];
} Ent;

typedef struct {
    char pad[0x10];
    unsigned short count;
} Tbl;

extern Tbl D_002D8840;
extern Ent *D_001ED6C0;

void func_001780D0(unsigned char mode) {
    int i;

    if (mode == 0) {
        for (i = 0; i < (int)D_002D8840.count; i++) {
            if ((unsigned int)(D_001ED6C0[i].id - 0x15C) < 0x64) {
                D_001ED6C0[i].flag = 0;
            }
        }
    } else if (mode == 1) {
        for (i = 0; i < (int)D_002D8840.count; i++) {
            if ((unsigned int)(D_001ED6C0[i].id - 1) < 0xFB) {
                D_001ED6C0[i].flag = 0;
            }
        }
    } else {
        for (i = 0; i < (int)D_002D8840.count; i++) {
            D_001ED6C0[i].flag = 0;
        }
    }
}
