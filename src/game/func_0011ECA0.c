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

void func_0011ECA0(int index, short *src) {
    if (src[0] != -1) {
        D_001FA9E8[index].h[0] = src[0];
    }
    if (src[1] != -1) {
        D_001FA9E8[index].h[1] = src[1];
    }
    if (src[2] != -1) {
        D_001FA9E8[index].h[2] = src[2];
    }
    if (src[3] != -1) {
        D_001FA9E8[index].h[3] = src[3];
    }
}
