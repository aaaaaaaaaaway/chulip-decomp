extern unsigned char D_001A6998[];
extern unsigned char D_001FDB00[];
extern unsigned char D_001FDB20[];
extern unsigned char D_001A5008[];
struct Name_001A6A38 { unsigned char text[0x11]; };
extern struct Name_001A6A38 D_001A6A38[];
extern void func_00192940(unsigned char *dst, unsigned char *src);

unsigned char *func_0012FAD8(unsigned char selector) {
    switch (selector) {
    case 1:
        return D_001FDB00;
    case 0:
        return D_001A6998;
    case 2:
        return D_001FDB20;
    case 3:
        return D_001A5008;
    }
    return 0;
}

void func_0012FB40(unsigned char index, unsigned char *dst) {
    if (index >= 0x5B) {
        index = index - 0x59;
    }
    func_00192940(dst, D_001A6A38[index].text);
}
