struct Node {
    int id;
    int type;
    short h08;
    short h0A;
    char pad0C[8];
    short h[4];
    int prev;
    int next;
};

extern struct Node D_001FA9E8[];

extern void func_0011E718(int index);

void func_0011E7F0(int id) {
    int i;

    for (i = 0; i < 0x90; i++) {
        if (D_001FA9E8[i].id == id) {
            func_0011E718(i);
        }
    }
}
