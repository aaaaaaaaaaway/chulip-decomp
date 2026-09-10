typedef struct {
    int field00, field04, field08, direction, field10, field14, cursor;
    int values[9];
    float scale;
    int field44;
    unsigned char unknown48[0x158];
} Ring;
extern Ring *D_001ED0F8[1];
extern int abs(int);
void func_0010A8D0(int index, int value) {
    int cursor = D_001ED0F8[0][index].cursor;
    if (D_001ED0F8[0][index].direction < 0) {
        cursor++;
        if (cursor >= 9)
            cursor -= 9;
    } else if (D_001ED0F8[0][index].direction == 0) {
        return;
    }
    D_001ED0F8[0][index].values[cursor] = value;
    D_001ED0F8[0][index].cursor -= D_001ED0F8[0][index].direction;
    if (D_001ED0F8[0][index].cursor < 0) {
        D_001ED0F8[0][index].cursor = 9 - abs(D_001ED0F8[0][index].cursor);
    }
    D_001ED0F8[0][index].cursor %= 9;
}
