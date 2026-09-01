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
extern int D_001FA9D0[];

void func_0011E718(int i) {
    if (D_001FA9E8[i].next != -1) {
        D_001FA9E8[D_001FA9E8[i].next].prev = D_001FA9E8[i].prev;
    }
    if (D_001FA9E8[i].prev != -1) {
        D_001FA9E8[D_001FA9E8[i].prev].next = D_001FA9E8[i].next;
    }
    if (i == D_001FA9D0[2]) {
        D_001FA9D0[2] = D_001FA9E8[i].prev;
    }
    if (i == D_001FA9D0[3]) {
        D_001FA9D0[3] = D_001FA9E8[i].next;
        if (D_001FA9E8[i].next == -1) {
            D_001FA9D0[2] = D_001FA9E8[i].next;
        }
    }
    D_001FA9E8[i].id = 0xFFFFFFFF;
    D_001FA9E8[i].prev = -1;
    D_001FA9E8[i].next = -1;
}
