typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector;

typedef struct Owner {
    unsigned char pad[0x10];
    void *node;
} Owner;

typedef struct {
    unsigned char pad[0x24];
    Owner *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];
extern void func_001335B8(void *node, unsigned short arg1, Vector *out);
extern void func_00156BC8(unsigned short index, Vector *value);
extern float func_00154720(unsigned short index);
extern void func_00156B00(unsigned short index, unsigned char slot, float value);

void func_0015C9E8(unsigned short index, unsigned short arg1, unsigned short target) {
    Vector local;
    Entry *entry = D_002ABA40 + index;

    func_001335B8(entry->owner->node, arg1, &local);
    func_00156BC8(target, &local);
    func_00156B00(target, 1, func_00154720(index));
}
