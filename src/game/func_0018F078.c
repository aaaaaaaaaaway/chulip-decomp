extern int D_001E3164[];
extern int D_001E317C[];
extern void func_0018F038(void);
extern int func_001A0828(void);
extern int func_001A0870(void);
extern int func_0019AB38(int code, void (*handler)(void), int argument);

int func_0018F078(void) {
    D_001E3164[0] = 1;
    func_001A0828();
    func_0019AB38(0x80000012, func_0018F038, 0);
    func_001A0870();
    D_001E3164[0] = 0;
    D_001E317C[0] = 1;
    return 1;
}
