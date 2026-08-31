/* object_flags: -Wa,-G4 */
struct S8_001ED260 { int field_0x0; int field_0x4; };

extern int D_001ED25C;
extern struct S8_001ED260 D_001ED260;

extern void func_00125498(int arg0);

void func_00124200(void) {
    D_001ED25C = -1;
    D_001ED260.field_0x0 = -1;
    func_00125498(3);
}
