typedef struct {
    unsigned char pad00[0x18];
    unsigned int flags;
} RenderNode;

typedef struct {
    unsigned char pad00[0x14];
    RenderNode *node;
} RenderHandle;

typedef struct {
    unsigned char pad00[0x24];
    RenderHandle *handle;
    unsigned char pad28[0x18];
} ActorSlot;

typedef struct {
    int unk00;
    unsigned int flags;
    unsigned char pad08[0x18];
} ActorFlags;

typedef struct {
    unsigned short owner;
    unsigned short part;
    unsigned short value;
} LinkSlot;

extern ActorSlot D_002ABA40[];
extern ActorFlags D_002CFA40[];
extern LinkSlot D_002D4480[];

void func_00158018(unsigned short owner, unsigned short part, unsigned short value,
                   unsigned short enable) {
    int i;
    RenderNode *node;

    if (enable != 0) {
        if ((D_002ABA40 + owner)->handle != 0) {
            node = (D_002ABA40 + owner)->handle->node;
            node->flags |= 0x20;
        }
        (D_002CFA40 + owner)->flags |= 0x20;
        if (value == 0xFFFF) {
            for (i = 0; i < 0x60; i++) {
                if (D_002D4480[i].owner == owner) {
                    break;
                }
            }
            if (i < 0x60) {
                D_002D4480[i].owner = 0xFFFF;
                D_002D4480[i].part = 0xFFFF;
            }
            return;
        }
        for (i = 0; i < 0x60; i++) {
            if (D_002D4480[i].owner == owner && D_002D4480[i].part == part) {
                if (D_002D4480[i].value != value) {
                    D_002D4480[i].value = value;
                }
                return;
            }
        }
        for (i = 0; i < 0x60; i++) {
            if (D_002D4480[i].owner == 0xFFFF) {
                break;
            }
        }
        D_002D4480[i].owner = owner;
        D_002D4480[i].part = part;
        D_002D4480[i].value = value;
        return;
    }
    if ((D_002ABA40 + owner)->handle != 0) {
        node = (D_002ABA40 + owner)->handle->node;
        node->flags &= ~0x20;
    }
    if (part == 0xFFFF) {
        for (i = 0; i < 0x60; i++) {
            if (D_002D4480[i].owner == owner) {
                D_002D4480[i].owner = 0xFFFF;
                D_002D4480[i].part = 0xFFFF;
                D_002D4480[i].value = 0xFFFF;
            }
        }
        return;
    }
    for (i = 0; i < 0x60; i++) {
        if (D_002D4480[i].owner == owner && D_002D4480[i].part == part) {
            D_002D4480[i].owner = 0xFFFF;
            D_002D4480[i].part = 0xFFFF;
            D_002D4480[i].value = 0xFFFF;
        }
    }
}
