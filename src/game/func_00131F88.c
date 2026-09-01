struct Entry_00131F88 { int field_0x0; int field_0x4; int field_0x8; int field_0xC; };

extern int func_00154700(unsigned short id);
extern struct Entry_00131F88 *func_001548A0(unsigned short id);
extern void func_00153518(int handle, int flag);
extern void func_00131F48(int handle);
extern void func_001546B8(int handle, int flag);
extern void func_00179938(int handle);

void func_00131F88(unsigned short id) {
    struct Entry_00131F88 *entry;
    int handle;

    handle = func_00154700(id);
    entry = func_001548A0(id);
    if (entry->field_0x4 != 0) {
        func_00153518(entry->field_0x4, 1);
    }
    if (entry->field_0xC != 0) {
        func_00131F48(entry->field_0xC);
        func_001546B8(handle, 1);
    }
    if (entry->field_0x8 != 0) {
        func_00179938(entry->field_0x8);
    }
}
