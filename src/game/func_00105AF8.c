struct S8_unsigned_short { unsigned short a; char pad[6]; };

extern short D_001ED088;
extern struct S8_unsigned_short D_001ED08A;

void func_00105AF8(void) {
    D_001ED088 = D_001ED08A.a;
}
