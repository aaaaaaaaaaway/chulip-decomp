typedef struct {
    unsigned short key;
    unsigned short index;
} Pair00174A88;

typedef struct {
    char pad00[0x6E];
    unsigned short id;
    char pad70[0x50];
} Ent00174A88;

typedef struct {
    unsigned int flags;
} Owner00174A88;

extern short D_001ECEF0;
extern Pair00174A88 D_002D8A10[];
extern Ent00174A88 *D_001ED6C0;
extern Owner00174A88 *D_001ED7E0;

int func_00156998(unsigned short id, unsigned short arg1, float value);

void func_00174A88(unsigned short key, unsigned short arg1, float value) {
    int i;

    for (i = 0; i < D_001ECEF0; i++) {
        if (D_002D8A10[i].key == key && (D_001ED7E0->flags & 0x800000) == 0) {
            func_00156998(D_001ED6C0[D_002D8A10[i].index].id, arg1, value);
        }
    }
}
