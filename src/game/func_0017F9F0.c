typedef int (*DrawCallback)(char *packet, int arg0, int arg1);
extern int D_001ED98C;
void func_00112F40(DrawCallback callback);
void func_0017F9F0(DrawCallback callback) {
    if (callback != 0) {
        func_00112F40(callback);
        D_001ED98C -= 1;
    }
}
