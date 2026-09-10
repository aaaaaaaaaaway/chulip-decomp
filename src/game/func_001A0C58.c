/* DECI2 open request, following the public kernel API and retail packet. */
extern unsigned char D_002E4128[];
extern int func_00198BD0(int operation, unsigned int *arguments);

int func_001A0C58(unsigned short protocol, void *option,
                  void (*handler)(int event, int parameter, void *option)) {
    unsigned int arguments[4];

    arguments[0] = protocol;
    arguments[1] = (unsigned int)option;
    arguments[2] = (unsigned int)handler;
    arguments[3] = (unsigned int)D_002E4128 | 0x20000000;
    return func_00198BD0(1, arguments);
}
