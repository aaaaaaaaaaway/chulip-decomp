typedef int (*DrawCallback)(char *packet, int arg0, int arg1);
extern int D_001ECFA8;
void func_0017F9B8(DrawCallback callback, int arg0, int arg1);
void func_0017F9F0(DrawCallback callback);

int func_0017FA28(char *packet, int limit, int next) {
    if (D_001ECFA8 >= limit) {
        D_001ECFA8 = 0;
        func_0017F9F0(func_0017FA28);
        if (next != 0) {
            func_0017F9B8((DrawCallback)next, limit, 0);
        }
    } else {
        D_001ECFA8 = D_001ECFA8 + 1;
    }
    return 0;
}
