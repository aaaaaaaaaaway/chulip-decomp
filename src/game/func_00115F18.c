typedef struct {
    unsigned short count;
    unsigned char pad;
    unsigned char size;
} Hdr;

extern unsigned char D_001ED1DD;
extern unsigned int D_001ED1E8;

float D_001EC8BC = 0.0f;
unsigned char D_001EC8C0 = 0;

int func_00113228(void *packet, int count);
int func_00115A50(void *packet, unsigned long first, unsigned long second);
int func_00115A78(void *packet, int x0, int y0, int x1, int y1,
                  int u0, int v0, int u1, int v1, int z, int color, long flags);
float func_0018B2F8(float angle);

int func_00115F18(unsigned char *dl)
{
    unsigned short pos[8][2] = {
        {0x00, 0x00}, {0x40, 0x00}, {0x80, 0x00}, {0xC0, 0x00},
        {0x00, 0x48}, {0x40, 0x48}, {0x80, 0x48}, {0xC0, 0x48},
    };
    Hdr *head;
    int used;
    int n;
    int i;
    int level;
    long color;
    float scale;
    unsigned short x0;
    unsigned short y0;
    unsigned short x1;
    unsigned short y1;

    if (D_001ED1DD == 0) {
        return 0;
    }

    *(long long *)dl = 0;
    head = (Hdr *)dl;
    dl += 0x10;
    head->size = 0x10;
    used = func_00113228(dl, 15);
    dl += used * 16;

    if (D_001ED1E8 < 180) {
        color = (180 - D_001ED1E8) * 128 / 180;
    }

    for (i = 0; i < 8; i++) {
        D_001EC8BC += 0.0061359233f;
        if (D_001EC8BC > 3.1415927f) {
            D_001EC8BC -= 6.2831855f;
        }
        if (((D_001EC8C0 >> i) & 1) == 0) {
            if (func_0018B2F8(D_001EC8BC) >= 1.0f) {
                D_001EC8C0 |= 1 << i;
            }
        }
        if (D_001ED1E8 < 60) {
            n = func_00115A50(dl, 0x47, 0x3000B);
            dl += n * 16;
            used += n;
            scale = 1.0f - (float)(60 - D_001ED1E8) / 60.0f;
            level = (int)(scale * 128.0f) & 0xFF;
            level = level ? level : 1;
            color = (int)0x80000000 | (level << 16) | (level << 8);
            color |= level;
            scale = 1.0f;
        } else if (D_001ED1E8 > 240) {
            n = func_00115A50(dl, 0x47, 0x3001B);
            dl += n * 16;
            used += n;
            scale = (float)(300 - D_001ED1E8) / 60.0f;
            color = ((int)(scale * 128.0f) << 24) | 0x606060;
        } else {
            color = 0x80606060;
            n = func_00115A50(dl, 0x47, 0x3001B);
            dl += n * 16;
            used += n;
            scale = 1.0f;
        }
        n = func_00115A50(dl, 0x42, ((unsigned long)(scale * 128.0f) << 32) | 0x64);
        dl += n * 16;
        used += n;

        if (i < 4) {
            x0 = pos[i][0] + 0xFF80;
            y0 = pos[i][1] + 0xFF92;
            x1 = x0 + 64;
            y1 = y0 + 72;
            n = func_00115A78(dl, x0, y0, x1, y1,
                              pos[i][0] * 16, pos[i][1] * 16,
                              (pos[i][0] + 64) * 16, (pos[i][1] + 72) * 16,
                              0xFFFFFF, color, 0);
        } else {
            x0 = pos[i][0] + 0xFF80;
            y0 = pos[i][1] + 0xFF92;
            x1 = x0 + 64;
            y1 = y0 + 56;
            n = func_00115A78(dl, x0, y0, x1, y1,
                              pos[i][0] * 16, pos[i][1] * 16,
                              (pos[i][0] + 64) * 16, (pos[i][1] + 56) * 16,
                              0xFFFFFF, color, 0);
        }
        dl += n * 16;
        used += n;
    }

    *(long *)dl = 0;
    used += 1;
    head->count = used;
    D_001ED1E8 += 1;
    return used + 1;
}
