/* Update active-entry flags across the current object set. */
struct State { unsigned char pad[16]; unsigned short count; };
struct Entry { unsigned int flags; unsigned char rest[188]; };
extern struct State D_002D8840;
extern int D_001ED6C0;
void func_00172440(void) {
    int i;
    for (i = 0; i < D_002D8840.count; i++) {
        if ((*(unsigned int *)(D_001ED6C0 + i * 0xC0)) & 2) {
            (*(unsigned int *)(D_001ED6C0 + i * 0xC0)) &= 0xFFFFFDFF;
            (*(unsigned int *)(D_001ED6C0 + i * 0xC0)) &= 0xFFFFFFFD;
            (*(unsigned int *)(D_001ED6C0 + i * 0xC0)) &= 0xFFFFFF7F;
        }
    }
}
