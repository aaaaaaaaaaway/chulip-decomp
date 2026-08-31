extern void func_00190F70(int arg0, int arg1, int arg2);
extern void func_00190848(int arg0, int arg1, int *out);
extern void func_001901A8(int arg0, int arg1, int arg2, int arg3);
extern void func_00190658(int arg0, int arg1, int arg2);
extern void func_00190318(int arg0);

int func_0014E550(int arg0, int arg1, int arg2) {
    int status;
    int handle;
    int result;

    func_00190F70(0, 0, arg0);
    func_00190848(0, 0, &status);
    func_001901A8(0, 0, arg0, 0x202);
    func_00190848(0, 0, &handle);
    if (handle < 0) {
        return handle;
    }
    func_00190658(handle, arg1, arg2);
    func_00190848(0, 0, &status);
    func_00190318(handle);
    func_00190848(0, 0, &result);
    if (status == -3) {
        func_00190F70(0, 0, arg0);
        func_00190848(0, 0, &status);
    }
    return status < 0 ? status : result;
}
