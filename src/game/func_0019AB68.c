typedef struct {
    int value;
    int unused;
} Entry;

extern Entry *D_002E0F24;
extern Entry *D_002E0F2C;

void func_0019AB68(int index)
{
    register int offset = index << 3;

    if (index < 0) {
        index = (int)D_002E0F24;
    } else {
        index = (int)D_002E0F2C;
    }
    offset += index;
    *(int *)offset = 0;
}
