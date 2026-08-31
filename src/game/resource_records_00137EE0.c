extern int *D_001EC9C0;
extern int *D_001EC9D0;
extern int *D_001EC9E0;
extern unsigned char D_00201BC0[16];

void func_00151CA8(int *object);
void func_00192940(void *destination, int value);

void func_00137EA0(void) {
    if (D_001EC9C0 != 0) {
        func_00151CA8(D_001EC9C0);
        D_001EC9C0 = 0;
    }

    if (D_001EC9D0 != 0) {
        func_00151CA8(D_001EC9D0);
        D_001EC9D0 = 0;
    }
}

void func_00137EE0(int index, int *output) {
    *output = *(int *)((unsigned char *)D_001EC9C0 + index * 8 + 8);
}

int func_00137EF8(int index) {
    return *(int *)((unsigned char *)D_001EC9C0 + index * 8 + 12);
}

void func_00137F10(int index, int *output) {
    *output = *(int *)((unsigned char *)D_001EC9D0 + index * 8 + 8);
}

int func_00137F28(int index) {
    return *(int *)((unsigned char *)D_001EC9D0 + index * 8 + 12);
}

void func_00137F40(void) {
    if (D_001EC9D0 != 0) {
        func_00151CA8(D_001EC9D0);
        D_001EC9D0 = 0;
    }
}

void func_00137F68(int index, int *output) {
    *output = *(int *)((unsigned char *)D_001EC9E0 + index * 8 + 8);
}

int func_00137F80(int index) {
    return *(int *)((unsigned char *)D_001EC9E0 + index * 8 + 12);
}

unsigned char *func_00137F98(void) {
    return D_00201BC0;
}

void func_00137FA8(int value) {
    func_00192940(D_00201BC0, value);
}
