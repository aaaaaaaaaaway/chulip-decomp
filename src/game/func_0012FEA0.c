struct Node_0012FEA0 {
    int field_0x0;
    struct Node_0012FEA0 *field_0x4;
    int field_0x8;
    int field_0xc;
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1c;
    int field_0x20;
};

extern void func_0012FD08(struct Node_0012FEA0 *node);
extern void func_00133150(int handle, unsigned short id);
extern void func_0015C4F0(unsigned short id);
extern void func_00100360(int handle, unsigned short id);
extern void func_0017A580(int handle, unsigned short id);

void func_0012FEA0(struct Node_0012FEA0 *node, unsigned short id) {
    if (node->field_0x4 != 0) {
        func_0012FD08(node->field_0x4);
    }
    if (node->field_0x10 != 0) {
        func_00133150(node->field_0x10, id);
    }
    if (node->field_0x14 != 0) {
        func_0015C4F0(id);
        func_00100360(node->field_0x14, id);
    }
    if (node->field_0x18 != 0) {
        func_0017A580(node->field_0x18, id);
    }
}
