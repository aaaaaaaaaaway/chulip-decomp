struct File { char pad0[0xC]; unsigned short flags; short handle; char pad10[0x40]; int position; int device; };
extern long func_001982B8(int device, int handle, int b, int c);

long func_00198058(struct File *file, int b, int c) {
    long result = func_001982B8(file->device, file->handle, b, c);
    if (result == -1) {
        file->flags = file->flags & 0xEFFF;
    } else {
        file->position = (int)result;
        file->flags = file->flags | 0x1000;
    }
    return result;
}
