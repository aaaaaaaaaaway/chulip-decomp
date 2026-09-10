/* File-I/O RPC write request. Completion semaphore entries are shared with
 * the SIF DMA interrupt callback. Unaligned leading bytes are copied into
 * the request packet before the aligned transfer. */
typedef struct {
    int fd, flags, f8, fC;
} Entry;
typedef struct {
    int f0, f4, f8, fC, f10, f14, f18, f1C;
} SemaParam;
typedef struct {
    int sema;
    int *rbuf;
    int rsize;
    int fd;
    unsigned char *buffer;
    int size;
    int prefix_size;
    unsigned char prefix[16];
    int index;
} WritePacket;
extern Entry D_002E3A00[];
extern int D_001E5B80[], D_001E5B8C[];
extern volatile int D_001E5B00[];
extern WritePacket D_002E2940;
extern int D_002E3580[], D_002E3C00[];
extern Entry *func_0019BF68(int fd);
extern int func_0019C3E8(int request);
extern void func_0019C418(void);
extern void func_0019AE70(void *addr, int size);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001987C0(int sema);
extern int func_001987E0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize, void *recv, int rsize,
                         void *endf, void *endp);
int func_0019D028(int fd, unsigned char *buffer, int size) {
    Entry *entry;
    WritePacket *packet = &D_002E2940;
    SemaParam param;
    int flags;
    int sema;
    int result;
    int status;
    int i, j;
    int prefix;
    entry = func_0019BF68(fd);
    func_0019C3E8(3);
    if (D_001E5B80[0] == 0) {
        func_0019C418();
        return -1;
    }
    if (entry == 0 || (flags = entry->flags) == 0) {
        func_0019C418();
        return -9;
    }
    packet->fd = entry->fd;
    packet->index = entry - D_002E3A00;
    packet->size = size;
    packet->buffer = buffer;
    param.f4 = 1;
    param.f8 = 0;
    param.f14 = 0;
    sema = func_001987A0(&param);
    packet->rbuf = &result;
    packet->rsize = 4;
    packet->sema = sema;
    if ((short)flags & 0x8000) {
        func_001987E0(D_001E5B8C[0]);
        for (i = 0; i < 32; i++) {
            if (D_001E5B00[i] == -1) {
                D_001E5B00[i] = packet->sema;
                packet->sema = -packet->sema;
                break;
            }
        }
        func_001987C0(D_001E5B8C[0]);
    }
    if (((int)buffer & 15) == 0)
        prefix = 0;
    else { /* Distance to the next 16-byte boundary, in 32-bit address arithmetic. */
        unsigned int before = (unsigned int)buffer - 16;
        prefix = ((unsigned int)buffer >> 4 << 4) - before;
    }
    if (size < prefix)
        prefix = size;
    if ((flags & 0x20000000) == 0)
        func_0019AE70(buffer, size);
    buffer = (unsigned char *)((int)buffer | 0x20000000);
    packet->prefix_size = prefix;
    for (j = 0; j < prefix; j++)
        packet->prefix[j] = buffer[j];
    if (func_0019B760(D_002E3C00, 3, 0, &D_002E2940, 0x30, D_002E3580, 4, 0, 0) < 0) {
        func_001987B0(sema);
        func_0019C418();
        return -11;
    }
    status = *(int *)((int)D_002E3580 | 0x20000000);
    func_0019C418();
    if (status == 0) {
        func_001987B0(sema);
        return -11;
    }
    if (flags & 0x8000) {
        func_001987B0(sema);
        return 0;
    }
    func_001987E0(sema);
    func_001987B0(sema);
    return result;
}
