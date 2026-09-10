typedef struct Slot3 {
    unsigned short f00;
    unsigned char pad02[6];
    unsigned short f08;
    unsigned short f0A;
} Slot3;

extern Slot3 D_002D48C0[];

void func_0015D280(unsigned short index);

void func_0015D238(unsigned short index, unsigned short a, unsigned short b, unsigned short c) {
    (D_002D48C0 + index)->f00 = a;
    D_002D48C0[index].f08 = b;
    D_002D48C0[index].f0A = c;
    func_0015D280(index);
}
