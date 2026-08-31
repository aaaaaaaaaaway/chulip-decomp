struct S_00139290 { unsigned char data[0x10]; };

extern struct S_00139290 D_00205070[];

extern void func_0018A680(int arg0, struct S_00139290 *arg1);

void func_00139290(unsigned char index, int arg1) {
    func_0018A680(arg1, &D_00205070[index]);
}
