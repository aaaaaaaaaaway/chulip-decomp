/* Resolve an object's interaction result through the appropriate script table. */
struct Entry {
    int flags;
    unsigned char pad[148];
    unsigned short interaction;
    unsigned char pad2[27];
    unsigned char script;
    unsigned char rest[10];
};
extern int D_001ED6C0;
extern int func_00173148(unsigned short);
extern int func_0012D548(int, int, int);
extern int func_0012D998(int, int, int);
extern int func_0012F5B8(unsigned char, int);
extern int func_00173340(int);

int func_00171E28(unsigned short id) {
    int index = func_00173148(id);
    int special = (((struct Entry *)D_001ED6C0)[index].flags >> 30) & 1;
    int result;

    if (!(((struct Entry *)D_001ED6C0)[index].interaction & 8)) {
        return 3;
    }
    if (((struct Entry *)D_001ED6C0)[index].script == 255) {
        return 4;
    }
    if (!(((struct Entry *)D_001ED6C0)[index].flags & 0x40000) && special == 1) {
        return 0;
    }
    if (special) {
        result = func_0012D548(((struct Entry *)D_001ED6C0)[index].script & 127, 6, 0);
    } else {
        result = func_0012D998(((struct Entry *)D_001ED6C0)[index].script, 6, 0);
    }
    if (func_00173340(func_0012F5B8(result, 3))) {
        return 2;
    } else {
        return 1;
    }
}
