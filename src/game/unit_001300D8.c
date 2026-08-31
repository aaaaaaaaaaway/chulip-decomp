typedef struct {
    unsigned char pad_00[0xC];
    float values_0C[8];
} Entry;

extern Entry *func_00136AE8(void);

void func_001300D8(short value0, short value1, short value2, short value3)
{
    Entry *entry = func_00136AE8();

    entry->values_0C[4] = value0;
    entry->values_0C[5] = value1;
    entry->values_0C[6] = value2;
    entry->values_0C[7] = value3;
}

void func_00130170(short value0, short value1, short value2, short value3)
{
    Entry *entry = func_00136AE8();

    entry->values_0C[0] = value0;
    entry->values_0C[1] = value1;
    entry->values_0C[2] = value2;
    entry->values_0C[3] = value3;
}
