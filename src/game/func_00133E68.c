/* object_flags: -Wa,-G4 */
struct Node_00133E68 {
    unsigned char pad_0x0[0x30];
    float field_0x30;
    float field_0x34;
    float field_0x38;
    unsigned char pad_0x3c[0x24];
};

struct Table_00133E68 { struct Node_00133E68 *nodes; int unused; };

extern struct Table_00133E68 D_001ED354;

void func_00133E68(int index, float x, float y, float z) {
    D_001ED354.nodes[index].field_0x30 = x;
    D_001ED354.nodes[index].field_0x34 = y;
    D_001ED354.nodes[index].field_0x38 = z;
}
