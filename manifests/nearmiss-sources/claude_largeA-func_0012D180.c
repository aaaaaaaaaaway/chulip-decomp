typedef struct {
    unsigned char pad00[0x49];
    unsigned char unk49;
    unsigned char pad4A[0x36];
} GameState;

typedef struct {
    unsigned char pad00[0x66];
    unsigned short unk66;
    unsigned char pad68[0x18];
} SoundObject;

extern GameState *func_00136AE8(void);
extern int func_00154508(int);
extern void func_00157510(int, int, int);
extern void func_00158C08(int, int);
extern void func_0015BA00(int);

extern SoundObject *D_001ED310;
extern unsigned char D_001FDB00[];
extern unsigned char D_001FDB02[];
typedef struct {
    unsigned char count;
    unsigned char pad01;
    unsigned char items[0x100];
} SoundTable;

extern SoundTable D_001A5008[];

void func_0012D180(unsigned char mode) {
    GameState *state;
    unsigned short id;
    int i;
    unsigned short sound;

    state = func_00136AE8();
    if (mode == 0xFF) {
        for (id = 0x3E0; id < 0x438; id++) {
            if (func_00154508(id) != 0) {
                func_00157510(id, 0, 0);
                func_00158C08(id, 0);
            }
        }
        func_00157510(0x43A, 0, 0);
        func_00158C08(0x43A, 0);
        return;
    }
    switch (mode) {
    case 1:
        for (i = 0; i < D_001FDB00[0]; i++) {
            sound = D_001ED310[D_001FDB02[i]].unk66;
            if (func_00154508(sound) != 0) {
                func_00157510(sound, 0, 0);
                func_0015BA00(sound);
                func_00158C08(sound, 1);
            }
        }
        func_00157510(0x43A, 0, 0);
        func_0015BA00(0x43A);
        func_00158C08(0x43A, 1);
        break;
    case 2:
        for (i = 0; i < D_001FDB00[0]; i++) {
            sound = D_001ED310[D_001FDB02[i]].unk66;
            if (func_00154508(sound) != 0) {
                func_00157510(sound, 2, 0);
                func_0015BA00(sound);
                func_00158C08(sound, 1);
            }
        }
        func_00157510(0x43A, 2, 0);
        func_0015BA00(0x43A);
        func_00158C08(0x43A, 1);
        break;
    case 3:
        for (i = 0; i < D_001A5008[state->unk49].count; i++) {
            sound = D_001ED310[D_001A5008[state->unk49].items[i]].unk66;
            if (func_00154508(sound) != 0) {
                func_00157510(sound, 2, 0);
                func_0015BA00(sound);
                func_00158C08(sound, 1);
            }
        }
        func_00157510(0x43A, 2, 0);
        func_0015BA00(0x43A);
        func_00158C08(0x43A, 1);
        break;
    case 4:
        for (id = 0x3E0; id < 0x438; id++) {
            if (func_00154508(id) != 0) {
                func_00157510(id, 2, 0);
                func_0015BA00(id);
                func_00158C08(id, 1);
            }
        }
        func_00157510(0x43A, 2, 0);
        func_0015BA00(0x43A);
        func_00158C08(0x43A, 1);
        break;
    }
}
