/* Initialize the memory-card RPC service and check its module versions. */
typedef struct {
    int fields[9];
    void *server;
} Client;
extern void func_0019AF20(int);
extern int func_0019B590(Client *, unsigned int, int);
extern int func_0019B760(Client *, int, int, void *, int, void *, int, void *, void *);
extern int func_001987C0(int);
typedef struct {
    int count, maximum, initial, waiters;
    unsigned int attributes, option;
} Semaphore;
extern int D_001E4BC4[], D_002DEC40[], D_002E0180[];
extern Client D_002DEBC0;
extern char D_001EBB88[], D_001EBBA0[], D_001EBBC8[];
extern int func_001987A0(Semaphore *);
extern int func_001987E0(int);
extern int func_00190848(int, int *, int *);
extern int func_00192508(const char *, ...);
int func_0018FE08(void) {
    Semaphore semaphore;
    int delay, result;
    if (D_001E4BC4[0] < 0) {
        semaphore.initial = 1;
        semaphore.maximum = 1;
        semaphore.option = 0;
        D_001E4BC4[0] = func_001987A0(&semaphore);
    }
    func_00190848(0, 0, 0);
    func_001987E0(D_001E4BC4[0]);
    func_0019AF20(0);
    for (;;) {
        if (func_0019B590(&D_002DEBC0, 0x80000400, 0) < 0) {
            func_00192508(D_001EBB88);
            for (;;) {
            }
        }
        if (D_002DEBC0.server)
            break;
        for (delay = 0x100000; delay != 0; --delay) {
        }
    }
    result = func_0019B760(&D_002DEBC0, 0xFE, 0, D_002DEC40, 0x30, D_002E0180, 12, 0, 0);
    func_001987C0(D_001E4BC4[0]);
    if (result < 0) {
        D_002DEBC0.server = 0;
        return result - 100;
    }
    if (D_002E0180[1] < 0x20A) {
        func_00192508(D_001EBBA0);
        D_002DEBC0.server = 0;
        return -120;
    }
    if (D_002E0180[2] < 0x20E) {
        func_00192508(D_001EBBC8);
        D_002DEBC0.server = 0;
        return -121;
    }
    return D_002E0180[0];
}
