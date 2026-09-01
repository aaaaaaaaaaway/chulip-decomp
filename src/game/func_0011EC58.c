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

short func_0011EC58(int id, unsigned short which) {
    int i;

    for (i = 0; i < 0x90; i++) {
        if (D_001FA9E8[i].id == id) {
            return D_001FA9E8[i].h[which];
        }
    }
    return -1;
}
