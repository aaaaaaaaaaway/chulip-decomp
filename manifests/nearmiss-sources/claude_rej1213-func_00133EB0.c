/* object_flags: -Wa,-G4 */
struct Node_00133EB0 { int field_0x0; unsigned char pad_0x4[0x5C]; };

struct Table_001ED350 { int count; struct Node_00133EB0 *nodes; };

extern struct Table_001ED350 D_001ED350;

void func_00133EB0(int index, int value) {
    int i;

    if (index == -1) {
        for (i = 0; i < D_001ED350.count; i++) {
            D_001ED350.nodes[i].field_0x0 = value;
        }
    } else {
        D_001ED350.nodes[index].field_0x0 = value;
    }
}
