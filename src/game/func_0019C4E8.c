/* Initialize file-I/O command callbacks, RPC binding and descriptor state. */
typedef struct {
    void (*handler)(void *);
    void *argument;
} Hook;
typedef struct {
    int descriptor;
    int flags;
    int field8;
    int fieldC;
} Entry;
typedef struct {
    int fields[9];
    void *server;
} Client;

extern Hook D_002E3C80[];
extern unsigned char D_002E3C40[];
extern Client D_002E3C00;
extern Entry D_002E3A00[];
extern int D_001E5B88[];
extern void *D_002E2900[];
extern unsigned char D_002E35C0[];
extern unsigned char D_002E3580[];
extern unsigned char D_002E3C28[];
extern int D_001E5B80[];

extern void func_0019AF20(int mode);
extern void func_001A0828(void);
extern void func_001A0870(void);
extern void func_0019AB38(int command, int handler, int argument);
extern void func_0019BFD8(void);
extern void func_0019C4B8(void);
extern int func_0019B590(Client *client, unsigned int sid, int mode);
extern void func_0019BE80(void);
extern int func_001987E0(int semaphore);
extern int func_001987C0(int semaphore);
extern int func_0019B760(void *client, int command, int mode, void *send, int send_size,
                         void *receive, int receive_size, void *callback, void *argument);

int func_0019C4E8(void) {
    Hook *hook = D_002E3C80;
    Entry *entry;
    int delay;

    func_0019AF20(0);
    hook->handler = 0;
    hook->argument = 0;
    func_001A0828();
    func_0019AB38(0x80000011, (int)func_0019BFD8, (int)D_002E3C40);
    func_0019AB38(0x80000013, (int)func_0019C4B8, (int)hook);
    func_001A0870();
    for (;;) {
        if (func_0019B590(&D_002E3C00, 0x80000001, 0) < 0)
            return -1;
        if (D_002E3C00.server != 0)
            break;
        for (delay = 0x100000; delay != -1; --delay) {
        }
    }
    func_0019BE80();
    func_001987E0(D_001E5B88[0]);
    for (entry = D_002E3A00; entry < D_002E3A00 + 32; ++entry)
        entry->flags = 0;
    func_001987C0(D_001E5B88[0]);
    D_002E2900[0] = D_002E35C0;
    if (func_0019B760(&D_002E3C00, 0xFF, 0, D_002E2900, 4, D_002E3580, 4, 0, 0) < 0)
        return -0x10001;
    __builtin_memcpy(D_002E3C28, (void *)((unsigned int)D_002E3580 | 0x20000000), 4);
    D_001E5B80[0] = 1;
    return 0;
}
