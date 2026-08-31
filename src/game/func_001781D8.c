struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED7C0;

int func_001781D8(int arg0) {
    return (D_001ED7C0.a + ((arg0 & 65535) * 48));
}
