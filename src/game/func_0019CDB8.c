/* File-I/O RPC read request. Completion semaphore entries are shared with
 * the SIF DMA interrupt callback. The async bit belongs to the low 16-bit
 * API flag field; the cached-transfer flag uses the full word. */
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
    int reserved18;
    int index;
} ReadPacket;
extern Entry D_002E3A00[];
extern int D_001E5B80[], D_001E5B8C[];
extern volatile int D_001E5B00[];
extern ReadPacket D_002E2940;
extern int D_002E3580[], D_002E3C00[];
extern unsigned char D_002E35C0[];
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
int func_0019CDB8(int fd, unsigned char *buffer, int size) {
    Entry *entry;
    ReadPacket *packet = &D_002E2940;
    SemaParam param;
    int flags;
    int sema;
    int result;
    int status;
    int i;
    entry = func_0019BF68(fd);
    func_0019C3E8(2);
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
    packet->buffer = buffer;
    packet->size = size;
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
    if ((flags & 0x20000000) == 0)
        func_0019AE70(buffer, size);
    func_0019AE70(D_002E35C0, 0xA4);
    func_0019AE70(packet, 0x20);
    if (func_0019B760(D_002E3C00, 2, 0, &D_002E2940, 0x20, D_002E3580, 4, 0, 0) < 0) {
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
