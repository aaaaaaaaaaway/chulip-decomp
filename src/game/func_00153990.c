extern int D_002C8A40[];
extern void func_00137F68(int channel, int *out);
extern int func_00137F80(int channel);
extern void func_00192344(int *context, int value, int handle);

void func_00153990(void) {
    int value;
    int handle;

    func_00137F68(1, &value);
    handle = func_00137F80(1);
    func_00137F68(1, &value);
    func_00192344(D_002C8A40, value, handle);
}
