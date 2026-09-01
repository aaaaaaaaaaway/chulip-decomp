typedef struct {
    unsigned char pad[0x20];
    volatile long long low : 16;
    volatile long long value : 32;
    volatile long long high : 16;
    float distance;
    unsigned char tail[0x14];
} Entry;

extern Entry D_002ABA40[];

float func_00154600(unsigned short index) {
    int flag = (D_002ABA40 + index)->value & 1;
    float result = 0.0f;

    if (flag) {
        result = (D_002ABA40 + index)->distance;
    }
    return result;
}
