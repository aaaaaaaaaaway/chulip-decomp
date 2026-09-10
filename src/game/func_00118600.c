extern int D_001ED1F4;

void func_00118890(void *entry, int count, float phase, float span);

void func_00118600(int index, int kind, float phase, float *velocity,
                   float *origin, int owner) {
    unsigned char *entry;
    unsigned char *clear;
    int i;

    entry = (unsigned char *)(D_001ED1F4 + index * 0x45C0);

    *(int *)(entry + 0x100) = owner;
    *(float *)(entry + 0x190) = origin[0];
    *(float *)(entry + 0x194) = origin[1];
    *(float *)(entry + 0x198) = origin[2];
    *(float *)(entry + 0x19C) = 1.0f;
    *(int *)(entry + 0x1A0) = 0x80;
    *(int *)(entry + 0x1A4) = 0x72;
    *(int *)(entry + 0x1A8) = 0x60;
    *(int *)(entry + 0x1AC) = 0x40;
    *(int *)(entry + 0x04) = 0;
    *(int *)(entry + 0x08) = 0;
    *(int *)(entry + 0x00) = kind;

    switch (kind) {
    case 0:
        *(int *)(entry + 0x10) = 0xFF;
        *(int *)(entry + 0x14) = 0xFF;
        *(int *)(entry + 0x18) = 0xA0;
        *(int *)(entry + 0x20) = 0x80;
        *(int *)(entry + 0x24) = 0xFF;
        *(int *)(entry + 0x28) = 0xFF;
        *(int *)(entry + 0x30) = 0xA0;
        *(int *)(entry + 0x34) = 0x80;
        *(int *)(entry + 0x38) = 0xFF;
        *(int *)(entry + 0x40) = 0xFF;
        *(int *)(entry + 0x44) = 0xFF;
        *(int *)(entry + 0x48) = 0xFF;
        break;
    case 1:
        *(int *)(entry + 0x10) = 0xDC;
        *(int *)(entry + 0x14) = 0xFF;
        *(int *)(entry + 0x18) = 0xC8;
        *(int *)(entry + 0x20) = 0xFF;
        *(int *)(entry + 0x24) = 0x80;
        *(int *)(entry + 0x28) = 0x40;
        *(int *)(entry + 0x30) = 0x80;
        *(int *)(entry + 0x34) = 0xFF;
        *(int *)(entry + 0x38) = 0xC8;
        *(int *)(entry + 0x40) = 0x80;
        *(int *)(entry + 0x44) = 0xFF;
        *(int *)(entry + 0x48) = 0xFF;
        break;
    case 2:
        *(int *)(entry + 0x10) = 0xC8;
        *(int *)(entry + 0x14) = 0xFF;
        *(int *)(entry + 0x18) = 0xFF;
        *(int *)(entry + 0x20) = 0x64;
        *(int *)(entry + 0x24) = 0x80;
        *(int *)(entry + 0x28) = 0xFF;
        *(int *)(entry + 0x30) = 0xFF;
        *(int *)(entry + 0x34) = 0xFF;
        *(int *)(entry + 0x38) = 0xFF;
        *(int *)(entry + 0x40) = 0;
        *(int *)(entry + 0x44) = 0;
        *(int *)(entry + 0x48) = 0;
        break;
    case 3:
        *(int *)(entry + 0x10) = 0xFF;
        *(int *)(entry + 0x14) = 0xFF;
        *(int *)(entry + 0x18) = 0xFF;
        *(int *)(entry + 0x20) = 0;
        *(int *)(entry + 0x24) = 0;
        *(int *)(entry + 0x28) = 0;
        *(int *)(entry + 0x30) = 0xFF;
        *(int *)(entry + 0x34) = 0x80;
        *(int *)(entry + 0x38) = 0xFF;
        *(int *)(entry + 0x40) = 0xC8;
        *(int *)(entry + 0x44) = 0xFF;
        *(int *)(entry + 0x48) = 0xC8;
        break;
    case 4:
        *(int *)(entry + 0x10) = 0x80;
        *(int *)(entry + 0x14) = 0x80;
        *(int *)(entry + 0x18) = 0xFF;
        *(int *)(entry + 0x20) = 0xC8;
        *(int *)(entry + 0x24) = 0xFF;
        *(int *)(entry + 0x28) = 0xFF;
        *(int *)(entry + 0x30) = 0;
        *(int *)(entry + 0x34) = 0;
        *(int *)(entry + 0x38) = 0;
        *(int *)(entry + 0x40) = 0;
        *(int *)(entry + 0x44) = 0;
        *(int *)(entry + 0x48) = 0;
        break;
    }

    func_00118890(entry, 0xA, phase, 259.0f);

    clear = entry;
    for (i = 7; i >= 0; i--) {
        *(int *)(clear + 0x60) = 0;
        *(int *)(clear + 0x64) = 0;
        *(int *)(clear + 0x68) = 0;
        *(int *)(clear + 0x6C) = 0;
        clear += 0x10;
    }

    *(float *)(entry + 0x60) = velocity[0];
    *(float *)(entry + 0x64) = velocity[1];
    *(float *)(entry + 0x68) = velocity[2];
    *(float *)(entry + 0x6C) = 1.0f;

    *(float *)(entry + 0xE0) = origin[0];
    *(float *)(entry + 0xE4) = origin[1];
    *(float *)(entry + 0xE8) = origin[2];
    *(float *)(entry + 0xEC) = 1.0f;

    *(int *)(entry + 0x50) = owner;
}
