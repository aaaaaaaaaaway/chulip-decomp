struct Source { char pad[0x14]; int f14; int f18; int f1C; int f20; int f24; int f28; };
struct Port { char pad[0x14]; int f14; int f18; int f1C; int f20; };
extern struct Port *func_0019B1B0(int handle);
extern void func_0019AD08(int a, struct Port *port, int c, int d, int e, int f);

void func_0019B2D8(struct Source *source, int handle) {
    struct Port *port = func_0019B1B0(handle);
    port->f14 = source->f14;
    port->f1C = source->f1C;
    port->f20 = 0x8000000C;
    func_0019AD08(0x80000008, port, 0x40, source->f20, source->f24, source->f28);
}
