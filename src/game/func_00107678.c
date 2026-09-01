extern int D_001ED0B4;
int func_00192568(void);

void func_00107678(int index) {
    *(int *)(index * 0x30 + D_001ED0B4 + 0xC) = func_00192568() % 0x168;
    *(int *)(index * 0x30 + D_001ED0B4 + 8) = 0;
    *(int *)(index * 0x30 + D_001ED0B4) = 1;
}
