/* Initialize SIF command receive state, handlers and IOP handshake. */
typedef void (*CommandFunction)(void *, void *);
typedef struct {
    CommandFunction function;
    void *argument;
} Handler;
/* Receive pools are stored as 32-bit EE bus addresses. */
typedef struct {
    unsigned int receive_buffer;
    unsigned int unused_buffer;
    unsigned int iop_buffer;
    Handler *system_handlers;
    int system_handler_count;
    Handler *user_handlers;
    int user_handler_count;
    int *software_registers;
} CommandState;
typedef struct {
    unsigned int header[3];
    int option;
    void *receive_buffer;
} AddressPacket;
extern int D_001E5AF4[];
extern unsigned char D_002E0E40[], D_002E0EC0[];
extern AddressPacket D_002E0F00;
extern int D_002E0F14[];
extern CommandState D_002E0F18;
extern Handler D_002E0F40[];
extern int D_002E1040[];
extern int func_001A0828(void), func_001A0870(void);
extern void func_0019A7F8(void *, void *), func_0019A7D8(void *, void *);
extern void func_00198A20(int);
extern void func_00198B80(void);
extern int func_0019AD48(int);
extern int func_001984B0(int, int (*)(int), int);
extern int func_001993B8(int);
extern unsigned int func_00198BB0(unsigned int);
extern int func_00198BA0(unsigned int, unsigned int);
extern int func_0019ACC8(unsigned int, void *, int, void *, void *, int);
void func_0019A850(void) {
    Handler *handler;
    int i;
    func_001A0828();
    if (D_001E5AF4[0]) {
        func_001A0870();
        return;
    }
    D_001E5AF4[0] = 1;
    D_002E0F18.receive_buffer = ((unsigned int)D_002E0E40 | 0x20000000);
    D_002E0F18.unused_buffer = ((unsigned int)D_002E0EC0 | 0x20000000);
    D_002E0F18.iop_buffer = 0;
    D_002E0F18.system_handlers = D_002E0F40;
    D_002E0F18.system_handler_count = 32;
    D_002E0F18.user_handlers = 0;
    D_002E0F18.user_handler_count = 0;
    D_002E0F18.software_registers = D_002E1040;
    handler = D_002E0F40;
    for (i = 0; i < 32; ++i) {
        handler->function = 0;
        handler->argument = 0;
        ++handler;
    }
    for (i = 0; i < 32; ++i)
        D_002E1040[i] = 0;
    D_002E0F40[0].function = func_0019A7F8;
    D_002E0F40[0].argument = &D_002E0F18;
    D_002E0F40[1].function = func_0019A7D8;
    D_002E0F40[1].argument = &D_002E0F18;
    func_001A0870();
    func_00198A20(0);
    if (*(volatile unsigned int *)0x1000E010 & 0x20)
        *(volatile unsigned int *)0x1000E010 = 0x20;
    if (!(*(volatile unsigned int *)0x1000C000 & 0x100))
        func_00198B80();
    D_002E0F14[0] = func_001984B0(5, func_0019AD48, 0);
    func_001993B8(5);
    D_002E0F18.iop_buffer = func_00198BB0(0x80000000);
    if (D_002E0F18.iop_buffer) {
        D_002E0F00.receive_buffer = D_002E0E40;
        func_0019ACC8(0x80000000, &D_002E0F00, 20, 0, 0, 0);
        return;
    }
    {
        while (!(func_00198BB0(4) & 0x20000)) {
        }
        D_002E0F18.iop_buffer = func_00198BB0(2);
        func_00198BA0(0x80000000, D_002E0F18.iop_buffer);
        func_00198BA0(0x80000001, (unsigned int)&D_002E0F18);
        D_002E0F00.receive_buffer = D_002E0E40;
        D_002E0F00.option = 0;
        func_0019ACC8(0x80000002, &D_002E0F00, 20, 0, 0, 0);
    }
}
