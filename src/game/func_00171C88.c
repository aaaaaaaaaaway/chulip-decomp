/* Clear three associations and release each linked entry's owner field. */
struct Entry {
    unsigned char pad[140];
    unsigned short links[3];
    unsigned char rest[46];
};
extern int D_001ED6C0, D_001ED680;

void func_00171C88(int index) {
    int i;
    int link;
    if (*(unsigned short *)(D_001ED6C0 + index * 192 + 140) != 0xFFFF) {
        for (i = 0; i < 3; i++) {
            link = ((struct Entry *)D_001ED6C0)[index].links[i];
            if (link != 0xFFFF) {
                *(unsigned short *)(D_001ED680 + 192 * link + 108) = 0xFFFF;
            }
            ((struct Entry *)D_001ED6C0)[index].links[i] = 0xFFFF;
        }
    }
}
