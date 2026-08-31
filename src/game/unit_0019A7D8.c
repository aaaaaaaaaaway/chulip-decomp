typedef struct SourceRecord {
    unsigned char unknown_00[0x10];
    int index_or_value_10;
    int value_14;
} SourceRecord;

typedef struct DestinationRecord {
    unsigned char unknown_00[8];
    int value_08;
    unsigned char unknown_0C[0x10];
    int *values_1C;
} DestinationRecord;

extern int D_002E1040[];

void func_0019A7D8(const SourceRecord *source, DestinationRecord *destination) {
    destination->values_1C[source->index_or_value_10] = source->value_14;
}

void func_0019A7F8(const SourceRecord *source, DestinationRecord *destination) {
    destination->value_08 = source->index_or_value_10;
}

int func_0019A808(int index) {
    return D_002E1040[index];
}

int func_0019A820(int index, int value) {
    D_002E1040[index] = value;
    return value;
}
