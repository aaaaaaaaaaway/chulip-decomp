extern int D_001ED570[2];
extern unsigned char D_001ED540;
extern unsigned char D_001ED541;
extern unsigned char D_001ED542;
extern unsigned char D_001ED543;
extern unsigned char D_001ED544;
extern unsigned char D_001ED545;

void *func_00136B80(int size);
int func_00189D50(int index, int zero, unsigned char *packet);

int func_00161B28(int index, int a, int b) {
    int result;

    if (func_00136B80(0x18) == 0) {
        return 0;
    }
    if (D_001ED570[index] != 1) {
        result = -1;
    } else {
        D_001ED540 = a;
        D_001ED541 = b;
        D_001ED542 = 0;
        D_001ED543 = 0;
        D_001ED544 = 0;
        D_001ED545 = 0;
        result = func_00189D50(index, 0, &D_001ED540);
    }
    return result;
}
