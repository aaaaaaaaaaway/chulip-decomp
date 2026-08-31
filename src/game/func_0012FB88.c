/* object_flags: -Wa,-G4 */
struct List_001FDB00 { unsigned char count; unsigned char limit; unsigned char entries[0x200]; };

struct Record_0012FB88 { unsigned char pad_0x0[0x66]; unsigned short field_0x66; unsigned char pad_0x68[0x18]; };

struct Table_001ED310 { struct Record_0012FB88 *records; int unused; };

extern struct List_001FDB00 D_001FDB00;
extern struct Table_001ED310 D_001ED310;

int func_0012FB88(unsigned short key) {
    int i;

    for (i = 0; i < D_001FDB00.count; i++) {
        if (D_001ED310.records[D_001FDB00.entries[i]].field_0x66 == key) {
            return 1;
        }
    }
    return 0;
}
