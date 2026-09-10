/* Preserve an entry in the snapshot pool and link it back to the live entry. */
struct Entry {
    unsigned int flags;
    char pad4[4];
    int angle;
    char padC[20];
    float position[4];
    char pad30[12];
    float height;
    char pad40[44];
    unsigned short owner, kind;
    char pad70[28];
    unsigned short links[3];
    char pad92[4];
    unsigned short token;
    char pad98[24];
    unsigned short state;
    char rest[14];
} __attribute__((aligned(16)));
extern int D_001ED6C0, D_001ED680;
extern float func_00154720(int index);
extern void func_00156BC8(unsigned short kind, float *position);
extern int func_00128158(float x, float z);
extern void func_00157D68(unsigned short kind);
extern int func_00158868(unsigned short kind, float *position);
extern unsigned short func_0015BD38(unsigned short kind);

unsigned short func_001715D8(int index) {
    unsigned short slot;
    struct Entry *entry;
    int i;
    if (index == 0) {
        ((struct Entry *)D_001ED6C0)[0].height = func_00154720(0);
    }
    entry = (struct Entry *)(index * 192 + D_001ED6C0);
    if (entry->flags & 0x08000000) {
        func_00156BC8(entry->kind, entry->position);
        entry->angle = func_00128158(entry->position[0], entry->position[2]);
        entry->flags &= 0xF7FFFFFF;
    }
    slot = 0;
    do {
        if (((struct Entry *)D_001ED680)[slot].state != 1) {
            break;
        }
        slot++;
    } while (slot < 432);
    if (((struct Entry *)D_001ED6C0)[index].kind != 0xFFFF) {
        func_00157D68(((struct Entry *)D_001ED6C0)[index].kind);
        func_00158868(((struct Entry *)D_001ED6C0)[index].kind,
                      ((struct Entry *)D_001ED6C0)[index].position);
        ((struct Entry *)D_001ED6C0)[index].token =
            func_0015BD38(((struct Entry *)D_001ED6C0)[index].kind);
    }
    ((struct Entry *)D_001ED680)[slot] = ((struct Entry *)D_001ED6C0)[index];
    *(unsigned int *)(D_001ED6C0 + index * 192) |= 8;
    *(unsigned short *)(D_001ED680 + slot * 192 + 176) = 1;
    i = 0;
    do {
        if (((struct Entry *)D_001ED6C0)[index].links[i] == 0xFFFF) {
            break;
        }
        i++;
    } while (i < 3);
    ((struct Entry *)D_001ED6C0)[index].links[i] = slot;
    return slot;
}
