extern int *D_002E0F24[];
extern int *D_002E0F2C[];

void func_0019AB68(int index) {
    int *table = (index < 0) ? D_002E0F24[0] : D_002E0F2C[0];
    table[index * 2] = 0;
}
