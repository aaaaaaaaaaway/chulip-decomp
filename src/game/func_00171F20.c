/* Compare script states or query the alternate object's condition. */
struct Entry {
    unsigned int flags;
    unsigned char pad[177];
    unsigned char script;
    unsigned char rest[10];
};
extern int D_001ED6C0;
extern int func_00173148(unsigned short);
extern int func_0012D548(int, int, int);
extern int func_0012D998(int, int, int);
extern int func_00173528(unsigned short);

int func_00171F20(unsigned short id) {
    unsigned char index = func_00173148(id);
    int first;
    int result;

    if (!(((struct Entry *)D_001ED6C0)[index].flags & 0x40000000)) {
        result = func_00173528(func_0012D998(((struct Entry *)D_001ED6C0)[index].script, 4, 0)) != 0;
    } else {
        first = func_0012D548(((struct Entry *)D_001ED6C0)[index].script & 127, 1, 0);
        result = first == func_0012D548(((struct Entry *)D_001ED6C0)[index].script & 127, 2, 0);
    }
    return result;
}
