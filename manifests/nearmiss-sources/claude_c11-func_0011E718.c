typedef struct {
    unsigned int id;
    int body[6];
    int prev;
    int next;
} Node;

extern Node D_001FA9E8[];
extern int D_001FA9D0[];

void func_0011E718(int index) {
    if (D_001FA9E8[index].next != -1) {
        D_001FA9E8[D_001FA9E8[index].next].prev = D_001FA9E8[index].prev;
    }
    if (D_001FA9E8[index].prev != -1) {
        D_001FA9E8[D_001FA9E8[index].prev].next = D_001FA9E8[index].next;
    }
    if (index == D_001FA9D0[2]) {
        D_001FA9D0[2] = D_001FA9E8[index].prev;
    }
    if (index == D_001FA9D0[3]) {
        D_001FA9D0[3] = D_001FA9E8[index].next;
        if (D_001FA9E8[index].next == -1) {
            D_001FA9D0[2] = D_001FA9E8[index].next;
        }
    }
    D_001FA9E8[index].id = 0xFFFFFFFF;
    D_001FA9E8[index].prev = -1;
    D_001FA9E8[index].next = -1;
}
