struct Record { char pad[0x10]; int f10; int f14; };
extern struct Record *func_00196F08(int a, int b);

void func_00197388(int a, int value) {
    struct Record *record = func_00196F08(a, 1);
    record->f14 = value;
    record->f10 = 1;
}
