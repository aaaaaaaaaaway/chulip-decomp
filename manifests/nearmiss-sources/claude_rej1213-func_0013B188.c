/* object_flags: -Wa,-G4 */
struct Value_001ED3D0 { short field_0x0; short pad[3]; };

extern struct Value_001ED3D0 D_001ED3D0;

extern void func_00101748(float value);
extern void func_00101AF8(void);

void func_0013B188(void) {
    func_00101748(D_001ED3D0.field_0x0 / 100.0f);
    func_00101AF8();
}
