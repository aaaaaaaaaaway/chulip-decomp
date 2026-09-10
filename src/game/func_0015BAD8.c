typedef struct Status {
    unsigned char unknown00[0x14];
    int field14, field18, mode;
    int field20;
    float field24, field28, field2C;
} Status;
typedef struct Owner {
    int unknown00;
    void *render;
    unsigned char unknown08[0xC];
    Status *status;
} Owner;
typedef struct Actor {
    unsigned char unknown00[0x20];
    union {
        long flags;
        struct {
            unsigned int low;
            Owner *owner;
        } link;
    } state;
    unsigned char unknown28[0x18];
} Actor;
typedef struct Snapshot {
    int default_mode, field04, field08, mode;
    float field10, field14, field18, field1C;
} Snapshot;
extern Actor D_002ABA40[];
extern Snapshot D_002CFA40[];
extern int func_00154398(unsigned short);
int func_0015BAD8(unsigned short index, int mode) {
    Status *status;
    if (index == 0xFFFF)
        return 0;
    if (!func_00154398(index) && index < 0x1C0) {
        if (D_002CFA40[index].mode != 0)
            return D_002CFA40[index].mode == mode;
        return D_002CFA40[index].default_mode == mode;
    }
    status = (D_002ABA40 + index)->state.link.owner->status;
    if (status == 0)
        return 0;
    if (status->mode == 0)
        return D_002CFA40[index].default_mode == mode;
    if (status->mode == mode)
        return 1;
    else
        return 0;
}
