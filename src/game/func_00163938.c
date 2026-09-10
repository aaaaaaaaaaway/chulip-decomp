extern char D_001E9D10[];
extern char D_001E9D20[];
extern char D_001E9D30[];

void func_001519F0(void);
void func_001667B0(const char *name, int slot);
void func_00163908(void);

void func_00163938(unsigned char flag) {
    func_001519F0();
    if (flag == 0) {
        func_001667B0(D_001E9D10, 0);
        func_001667B0(D_001E9D20, 1);
        func_001667B0(D_001E9D30, 2);
    } else {
        func_001667B0(D_001E9D10, 3);
        func_001667B0(D_001E9D20, 4);
        func_001667B0(D_001E9D30, 5);
    }
    func_001519F0();
    func_00163908();
}
