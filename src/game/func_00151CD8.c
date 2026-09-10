/* Clear unallocated arena gaps using the initialized allocation-list head. */
typedef unsigned int u32;
typedef struct Range {
    u32 begin, end;
} Range;
extern Range D_00288E80[];
extern Range D_00294E84[];
extern Range D_002A0E80[];
extern u32 D_001ED458;
u32 D_001ECBD0 = 0xFFFFFFFF;
extern u32 D_001ECBCC;
extern u32 D_001ECBD8;
extern void func_00151E68(u32, u32);
extern void func_00198A20(int);
extern void *func_001923F4(void *, int, unsigned int);
void func_00151CD8(void) {
    u32 current = D_001ED458;
    u32 end = current + 0x1A00000;
    u32 cursor;
    int count = 0, i;
    Range *gap;
    cursor = D_001ECBD0;
    if (cursor != 0xFFFFFFFF) {
        gap = D_002A0E80;
        for (; cursor != 0xFFFFFFFF; cursor = D_00294E84[cursor].begin) {
            if (current == D_00288E80[cursor].begin) {
                current = D_00288E80[cursor].end;
            } else {
                gap->begin = current;
                gap->end = D_00288E80[cursor].begin;
                ++count;
                current = D_00288E80[cursor].end;
                ++gap;
            }
        }
    }
    if (current != end) {
        D_002A0E80[count].begin = current;
        D_002A0E80[count].end = end;
        ++count;
    }
    for (i = 0; i < count; ++i) {
        func_001923F4((void *)D_002A0E80[i].begin, 0, D_002A0E80[i].end - D_002A0E80[i].begin);
    }
    func_00198A20(0);
}
