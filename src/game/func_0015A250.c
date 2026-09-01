typedef union {
    long flags;
    struct {
        int lo;
        int f24;
    } w;
} SlotHead;

typedef struct {
    char pad0[0x20];
    SlotHead head;
    char pad1[0x18];
} Slot;

typedef struct {
    long flags;
} Ctl;

extern unsigned short D_002AAF00[];
extern Slot D_002ABA40[];

Ctl *func_00136AE8(void);
void func_0015A4E0(int id);
void func_00155920(int id);
void func_00198A20(int a);

void func_0015A250(void) {
    Ctl *ctl;
    int i;
    int on;
    int id;
    Slot *sl;

    i = 0;
    ctl = func_00136AE8();
    on = (int)(ctl->flags >> 3) & 1;
    while (D_002AAF00[i] != 0xFFFF && i < 0x1E0) {
        id = D_002AAF00[i];
        sl = &D_002ABA40[id];
        if (((int)(sl->head.flags >> 2) & 1) == 0) {
            if (on != 0) {
                if (sl->head.w.f24 != 0) {
                    func_0015A4E0(id);
                }
            }
            func_00155920(id);
        }
        D_002AAF00[i] = 0xFFFF;
        i++;
    }
    if (on != 0) {
        ctl->flags = ctl->flags & ~8;
    }
    func_00198A20(0);
}
