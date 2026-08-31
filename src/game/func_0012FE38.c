struct Scene_0012FE38 {
    unsigned char pad_0x0[0x4];
    int field_0x4;
    unsigned char pad_0x8[0x8];
    int field_0x10;
    unsigned char pad_0x14[0x4];
    int field_0x18;
};

extern void func_0012FD08(int arg0);
extern void func_00133150(int arg0, unsigned short arg1);
extern void func_0017A580(int arg0, unsigned short arg1);

void func_0012FE38(struct Scene_0012FE38 *scene, unsigned short arg1) {
    if (scene->field_0x4 != 0) {
        func_0012FD08(scene->field_0x4);
    }
    if (scene->field_0x10 != 0) {
        func_00133150(scene->field_0x10, arg1);
    }
    if (scene->field_0x18 != 0) {
        func_0017A580(scene->field_0x18, arg1);
    }
}
