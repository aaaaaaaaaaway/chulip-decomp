extern int *D_001EC9C0;
extern int *D_001EC9D0;
extern char D_001E7C08[];
extern char D_001E7C20[];

void func_00151CA8(int *object);
int func_00192940(void *destination, void *source);
void func_001926D0(void *destination, void *source);
void func_00125ED0(char *path, int **destination, int offset, int size, int flags);
void *func_00137F98(void);

void func_00137CC0(unsigned char mode) {
    char path[32];
    int base;
    unsigned int i;

    if (mode == 0 || mode == 2) {
        if (D_001EC9C0 != 0) {
            func_00151CA8(D_001EC9C0);
            D_001EC9C0 = 0;
        }
    }

    if (mode < 2) {
        if (D_001EC9D0 != 0) {
            func_00151CA8(D_001EC9D0);
            D_001EC9D0 = 0;
        }
        func_00192940(path, func_00137F98());
        func_001926D0(path, D_001E7C08);
        func_00125ED0(path, &D_001EC9D0, 0, -1, 0);
        base = (int)D_001EC9D0;
        for (i = 0; i < 28; i++) {
            if (*(int *)((unsigned char *)D_001EC9D0 + i * 8 + 8) != 0) {
                *(int *)((unsigned char *)D_001EC9D0 + i * 8 + 8) += base;
            }
        }
    }

    if (mode == 0 || mode == 2) {
        func_00192940(path, func_00137F98());
        func_001926D0(path, D_001E7C20);
        func_00125ED0(path, &D_001EC9C0, 0, -1, 0);
        base = (int)D_001EC9C0;
        for (i = 0; i < 10; i++) {
            if (*(int *)((unsigned char *)D_001EC9C0 + i * 8 + 8) != 0) {
                *(int *)((unsigned char *)D_001EC9C0 + i * 8 + 8) += base;
            }
        }
    }
}
