typedef struct RenderState RenderState;
typedef struct Status {
    unsigned char unknown00[0x14];
    int field14, field18, mode;
    int field20;
    float field24, field28, field2C;
} Status;
typedef struct Owner {
    int unknown00;
    RenderState *render;
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
typedef struct ModelRef {
    unsigned int unknown00[2];
    unsigned int *model;
} ModelRef;
extern unsigned int func_001513E0(int, int, int);
extern void func_00153618(int, RenderState *);
void func_0015BE88(unsigned short index, unsigned char kind, unsigned char enabled) {
    Actor *actor = D_002ABA40 + index;
    if (actor->state.link.owner == 0)
        return;
    switch (kind) {
    case 2:
        if (enabled) {
            actor->state.flags |= 0x100L;
            func_00153618(2, actor->state.link.owner->render);
        } else {
            actor->state.flags &= ~0x100L;
            func_00153618(1, actor->state.link.owner->render);
        }
        break;
    case 1: {
        ModelRef *ref = (ModelRef *)func_001513E0(0x12, index, 0);
        unsigned int *cursor = ref->model;
        unsigned int count = cursor[3];
        unsigned int i;
        if (enabled)
            actor->state.flags |= 0x1000L;
        else
            actor->state.flags &= ~0x1000L;
        cursor += 4;
        for (i = 0; i < count; ++i) {

            if (enabled)
                cursor[1] |= 8;
            else
                cursor[1] &= ~8U;
            cursor += 4;
            {
                unsigned int count0 = cursor[0];
                unsigned int count1 = cursor[1];
                cursor += 4;
                cursor += count0;
                cursor += count1;
            }
        }
        break;
    }
    }
}
