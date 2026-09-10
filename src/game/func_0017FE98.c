typedef struct {
    int flags;
    int x, y, z;
    int u, v, w, h;
    int unused20;
    float sx, sy;
    unsigned char r, g, b, a;
} Sprite;

extern int D_002DB540[];
void *func_001923F4(void *destination, int value, unsigned int size);
int func_00161FE0(int port, int which);
void func_0017F898(void);
typedef int (*DrawCallback)(char *packet, int arg0, int arg1);
void func_0017F9B8(DrawCallback callback, int arg0, int arg1);
int func_0017FA98(char *packet, int index, int unused);
int func_0017FA28(char *packet, int limit, int next);
int func_00180AC8(char *packet, int index, int unused);
int func_00113228(char *packet, int texture);
int func_00119840(char *packet, Sprite *sprite);

int func_0017FE98(char *packet, int index, int unused) {
    Sprite sprite;
    int x[] = {128, 176, 218, 261, 287, 312, 334};
    int y[] = {68, 68, 68, 68, 68, 68, 68};
    int u[] = {0, 54, 105, 154, 188, 218, 0};
    int v[7];
    func_001923F4(v, 0, sizeof(v));
    v[6] = 80;
    {
        int width[] = {54, 51, 49, 34, 30, 30, 47};
        int height[] = {80, 80, 80, 80, 80, 80, 80};
        char *start;
        int count;

        if (D_002DB540[index] < 16) {
            if ((func_00161FE0(0, 1) & 0x20) || (func_00161FE0(0, 1) & 0x800)) {
                func_0017F898();
                func_0017F9B8(func_0017FA98, index, 0);
                return 0;
            }
        }
        start = packet;
        packet += 16;
        start[3] = 0x10;
        count = func_00113228(packet, 27);
        packet += count * 16;
        *(unsigned long *)packet = 0x1000000000008001UL;
        *(unsigned long *)(packet + 8) = 0xE;
        *(unsigned long *)(packet + 24) = 0x42;
        *(unsigned long *)(packet + 16) = 0x8000000044UL;
        packet += 32;
        count += 2;
        sprite.flags = 0;
        sprite.x = (x[index] + 0x700) << 4;
        sprite.y = (y[index] / 2 + 0x790) << 4;
        sprite.z = 0x07FFFFF0;
        sprite.u = u[index] << 4;
        sprite.v = v[index] << 4;
        sprite.w = width[index] << 4;
        sprite.h = height[index] << 4;
        sprite.sx = 1.0f;
        sprite.sy = 0.5f;
        sprite.r = 128;
        sprite.g = 128;
        sprite.b = 128;
        if (D_002DB540[index] < 16)
            sprite.a = (D_002DB540[index] << 7) / 15;
        else
            sprite.a = 128;
        if ((unsigned int)(D_002DB540[index] - 16) < 9) {
            float amount = ((D_002DB540[index] - 15) * 0.5f) / 10.0f;
            sprite.sy = amount + 0.5f;
            sprite.y += (amount * -80.0f) * 16.0f;
        } else if (D_002DB540[index] >= 25) {
            float amount = ((D_002DB540[index] - 25) * 0.5f) / 10.0f;
            sprite.sy = 1.0f - amount;
            sprite.y += (amount * 80.0f) * 16.0f + -640.0f;
        }
        count += func_00119840(packet, &sprite);
        if (++D_002DB540[index] == 15) {
            ++index;
            D_002DB540[index] = 0;
            switch (index) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                func_0017F9B8(func_0017FE98, index, 0);
                break;
            case 7:
                func_0017F9B8(func_0017FA28, 30, (int)func_00180AC8);
                break;
            }
        } else if (D_002DB540[index] >= 36) {
            D_002DB540[index] = 35;
        }
        *(unsigned short *)start = count;
        return count + 1;
    }
}
