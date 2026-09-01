extern int D_001E3150[];
extern int D_001EBAC0[];
extern int D_001E4B88[];
extern void func_0019A778(int *format, ...);
extern void func_0018EB18(int id);
extern int func_0019B950(int *handle);

int func_0018F688(int flag) {
    if (flag == 0) {
        if (D_001E3150[0] > 0) {
            func_0019A778(D_001EBAC0);
        }
        while (func_0019B950(D_001E4B88) != 0) {
            func_0018EB18(0x3C);
        }
        return 0;
    }
    return func_0019B950(D_001E4B88);
}
