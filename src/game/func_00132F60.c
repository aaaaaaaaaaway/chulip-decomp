/* object_flags: -Wa,-G4 */
struct Pair_001ED344 { int field_0x0; int field_0x4; };

extern int D_001ED340;
extern struct Pair_001ED344 D_001ED344;

extern int func_00132F90(int index);

void func_00132F60(void) {
    D_001ED340 = func_00132F90(0);
    D_001ED344.field_0x0 = func_00132F90(1);
}
