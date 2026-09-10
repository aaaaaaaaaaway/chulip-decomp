/* Mark an object and return the next integral threshold while below its limit. */
struct Limit {
    unsigned char pad[162];
    unsigned short limit;
};
extern struct Limit *D_001ED7E0;
extern float D_001ED824;
extern int D_001ED6C0;

int func_00171058(int index) {
    if (D_001ED824 < (float)D_001ED7E0->limit) {
        *(unsigned int *)(D_001ED6C0 + index * 192 + 4) |= 0x20000000;
        return (int)D_001ED824 + 1;
    }
    return 0;
}
