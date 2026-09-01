typedef struct { int a; int b; } Slot;

extern Slot *D_002E0F24[];
extern Slot *D_002E0F2C[];

void func_0019AB38(int index, int a, int b) {
    if (index < 0) {
        D_002E0F24[0][index].a = a;
        D_002E0F24[0][index].b = b;
    } else {
        D_002E0F2C[0][index].a = a;
        D_002E0F2C[0][index].b = b;
    }
}
