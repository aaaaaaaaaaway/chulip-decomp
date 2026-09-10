/* Refresh the temporary actor range and both registered scene lists. */
struct Node_0012FEA0;
struct Node_0012FDB0;
struct Scene_0012FE38;
struct A;
struct Owner;
typedef struct {
    unsigned short id, unknown02;
} Slot;
extern Slot D_002D71C0[];
extern Slot D_002D66C0[];
extern int D_001ED490;
extern int D_001ED480;
int func_00154398(unsigned short);
void *func_001548A0(unsigned short);
void func_0012FEA0(struct Node_0012FEA0 *, unsigned short);
void func_0012FDB0(struct Node_0012FDB0 *, unsigned short);
void func_0012FE38(struct Scene_0012FE38 *, unsigned short);
void func_00101020(struct A *);
int func_00158830(unsigned short, unsigned short);
void func_00135FA0(struct Owner **, unsigned char);
void func_00135C50(void *);
int func_00154638(unsigned short);
unsigned char func_00158678(unsigned short);

void func_0012FF28(void) {
    int i;
    void *actor;
    int id;
    for (i = 0x47f; i >= 0x3e0; i--) {
        id = i;
        if (func_00154398(id)) {
            actor = func_001548A0(id);
            func_0012FEA0(actor, id);
            func_00101020(actor);
            if (func_00158830(id, 0))
                func_00135FA0(actor, 0);
            else
                func_00135C50(actor);
        }
    }
    for (i = 0; i < D_001ED490; i++) {
        id = D_002D71C0[i].id;
        if (func_00154398(id)) {
            actor = func_001548A0(id);
            func_0012FDB0(actor, id);
            if (func_00154638(id))
                func_00135FA0(actor, func_00158678(id));
            else
                func_00135C50(actor);
            func_00101020(actor);
        }
    }
    for (i = 0; i < D_001ED480; i++) {
        id = D_002D66C0[i].id;
        if (func_00154398(id)) {
            actor = func_001548A0(id);
            func_0012FE38(actor, id);
            func_00101020(actor);
            func_00135C50(actor);
        }
    }
}
