/* Activate visible entries according to their interaction flags. */
struct State { unsigned char pad[16]; unsigned short count; };
struct Entry { unsigned int flags; unsigned char pad[148]; unsigned short interaction; unsigned char rest[38]; };
extern struct State D_002D8840;
extern int D_001ED6C0;
extern int func_001711A0(int index);
extern int func_00170C40(unsigned short index, float angle);
void func_001722B0(void) {
    int i;
    for (i = 0; i < D_002D8840.count; i++) {
        if (((struct Entry *)D_001ED6C0)[i].interaction & 0x1010) {
            if (func_001711A0(i)) {
                if (func_00170C40(i, 1.5707963705f)) {
                    if (((struct Entry *)D_001ED6C0)[i].interaction & 0x1000) {
                        *(unsigned int *)(D_001ED6C0 + i * 192) |= 0x80;
                    } else if (((struct Entry *)D_001ED6C0)[i].interaction & 0x10) {
                        *(unsigned int *)(D_001ED6C0 + i * 192) |= 0x200;
                        *(unsigned int *)(D_001ED6C0 + i * 192) |= 2;
                    }
                }
            }
        }
    }
}
