struct S_00139260 { unsigned char data[0x10]; };

extern struct S_00139260 D_00205070[];

extern void func_0018A680(struct S_00139260 *arg0, int arg1);

void func_00139260(unsigned char index, int arg1) {
    func_0018A680(&D_00205070[index], arg1);
}
