typedef struct {
    char *pointers[2];
    int capacity;
} DrawList;
extern DrawList D_002D81B0;
extern long *D_001EC96C;
extern void func_00161590(int, int);
extern void func_00161460(int, int);
extern void func_001614E0(int, int, int);
extern int func_00113228(void *, int);

void func_00131780(void) {
    long *packet = (long *)D_002D81B0.pointers[1];
    D_001EC96C = packet;
    func_00161590((int)packet, 21);
    func_00161460((int)packet, 21);
    func_001614E0((int)packet, 3, 21);
    packet += 2;
    packet += func_00113228(packet, 1) * 2;
    /* Textured sprite 1: tag, register list, primitive, color, vertices. */
    *packet++ = 0x6400000000008001L;
    *packet++ = 0x0000000000535310L;
    *packet++ = 0x0000000000000156L;
    *packet++ = 0x0000000180808080L;
    *packet++ = 0x0000000000000000L;
    *packet++ = 0x0000000079007400L;
    *packet++ = 0x0000000008000800L;
    *packet++ = 0xFFFFFFFF80008000L;
    /* Textured sprite 2: tag, register list, primitive, color, vertices. */
    *packet++ = 0x6400000000008001L;
    *packet++ = 0x0000000000535310L;
    *packet++ = 0x0000000000000156L;
    *packet++ = 0x0000000180808080L;
    *packet++ = 0x0000000000000800L;
    *packet++ = 0x0000000079008000L;
    *packet++ = 0x0000000008001000L;
    *packet++ = 0xFFFFFFFF80008C00L;
    /* Textured sprite 3: tag, register list, primitive, color, vertices. */
    *packet++ = 0x6400000000008001L;
    *packet++ = 0x0000000000535310L;
    *packet++ = 0x0000000000000156L;
    *packet++ = 0x0000000180808080L;
    *packet++ = 0x0000000008000000L;
    *packet++ = 0xFFFFFFFF80007400L;
    *packet++ = 0x0000000010000800L;
    *packet++ = 0xFFFFFFFF87008000L;
    /* Textured sprite 4: tag, register list, primitive, color, vertices. */
    *packet++ = 0x6400000000008001L;
    *packet++ = 0x0000000000535310L;
    *packet++ = 0x0000000000000156L;
    *packet++ = 0x0000000180808080L;
    *packet++ = 0x0000000008000800L;
    *packet++ = 0xFFFFFFFF80008000L;
    *packet++ = 0x0000000010001000L;
    *packet++ = 0xFFFFFFFF87008C00L;
    func_00161590((int)packet, 0);
    packet += 2;
    D_002D81B0.pointers[1] = (char *)packet;
}
