extern int D_001ECB70;
extern int D_001ECB74;
extern int D_001ECB78;
extern int D_001ECB7C;
extern void func_0014FF28(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
extern void func_00150A58(void);
extern void func_00112F40(void (*entry)(void));
extern void func_00112EB0(void (*entry)(void), int arg1, int arg2);

void func_00151270(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    D_001ECB78 = arg0;
    D_001ECB70 = arg1;
    D_001ECB74 = arg2;
    D_001ECB7C = 1;
    func_0014FF28(arg3, arg4, arg5, 0, 0, 0, 0);
    func_00112F40(func_00150A58);
    func_00112EB0(func_00150A58, 0, 0);
}
