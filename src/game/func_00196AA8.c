typedef struct {
    char pad0[0x30];
    void *unk30;
    const char *unk34;
} Object;

extern char D_001EBFC8[];
extern char D_001EBFB8[];
extern int func_001927FC(const char *a, const char *b);

char *func_00196AA8(Object *object, void *value, const char *name) {
    if (name != 0) {
        if (func_001927FC(name, D_001EBFC8) != 0 &&
            func_001927FC(name, D_001EBFB8) != 0) {
            return 0;
        }
        object->unk30 = value;
        object->unk34 = name;
    }
    return D_001EBFC8;
}
