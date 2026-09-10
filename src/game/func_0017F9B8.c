typedef int (*DrawCallback)(char *packet, int arg0, int arg1);
extern int D_001ED98C;
void func_00112EB0(DrawCallback callback, int arg0, int arg1);
void func_0017F9B8(DrawCallback callback, int arg0, int arg1) {
    if (callback != 0) {
        func_00112EB0(callback, arg0, arg1);
        D_001ED98C += 1;
    }
}
