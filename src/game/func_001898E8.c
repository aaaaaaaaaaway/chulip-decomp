extern char *D_001E30C8[];
extern unsigned char D_001EB0E8[];
extern void func_00192940(char *destination, char *source);

void func_001898E8(int index, char *destination) {
    if ((unsigned int)index < 4) {
        func_00192940(destination, D_001E30C8[index]);
    } else {
        *destination = D_001EB0E8[0];
    }
}
