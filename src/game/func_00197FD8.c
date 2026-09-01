struct File { char pad0[0xC]; unsigned short flags; short handle; char pad10[0x44]; int *slot; };
extern long func_001982B8(int *slot, int handle, int b, int c);
extern long func_001980E0(int *slot, int handle, int b, int c);

int func_00197FD8(struct File *file, int b, int c) {
    unsigned short flags = file->flags;
    if (flags & 0x100) {
        func_001982B8(file->slot, file->handle, 0, 2);
    }
    file->flags = file->flags & 0xEFFF;
    return (int)func_001980E0(file->slot, file->handle, b, c);
}
