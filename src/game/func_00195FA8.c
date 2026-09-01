typedef struct {
    int unk0;
    int count;
    void *data;
} Block;

extern Block *func_00191B38(void *arg, int size);
extern void func_001923F4(void *dst, int value, int size);

Block *func_00195FA8(void *arg, int count) {
    Block *block;
    void *data;
    int size;

    size = count * 0x58;
    block = func_00191B38(arg, size + 0xC);
    if (block == 0) {
        return 0;
    }
    data = block + 1;
    block->count = count;
    block->unk0 = 0;
    block->data = data;
    func_001923F4(data, 0, size);
    return block;
}
