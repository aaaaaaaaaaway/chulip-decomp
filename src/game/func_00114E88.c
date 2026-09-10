/* Builds one DMA chain packet for the fade/overlay layer.
 *
 * The caller hands over a scratch buffer.  Word 0 of the buffer is the DMA
 * tag: its low halfword is the qword count, byte 3 carries the tag id, and
 * the rest of the chain is appended qword by qword by the packet helpers,
 * each of which returns the number of qwords it wrote.
 */

extern int D_001ED1C0;
extern int D_001ED1C4;

/* Small-data word provisionally defined here; func_00114E38 stores the active layer
 * id into it and both functions read it through $gp. */
int D_001EC8B8 = 1;

int func_00114D70(void *dst, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9, int a10, int a11, int a12,
                  int a13, int a14);
int func_00187920(void *dst, int mode, short a3, short a4, short a5,
                  short a6, short a7, short a8, short a9, short a10,
                  short a11, short a12);
int func_00113648(void *dst, unsigned long first, unsigned long second);
int func_00113670(void *dst, int ax, int ay, int bx, int by, int u0, int v0,
                  int u1, int v1, int z, int extra);
void func_0017E9B0(int block);

int func_00114E88(unsigned char *p) {
    unsigned char *chain;
    unsigned char *body;
    long *gif;
    int qwords;
    int written;
    int added;

    qwords = 0;
    *(long long *)p = 0;
    chain = p;
    chain[3] = 0x10;
    p = chain + 0x10;

    if (D_001ED1C4 == D_001EC8B8) {
        qwords = func_00114D70(p, 0, 8, 0, 0, 0, D_001ED1C0, 8, 0, 0, 0,
                               0x200, 0xE0, 0);
        p += qwords * 16;
    }

    if (D_001ED1C4 > 0) {
        body = p + 0x10;
        *(long long *)p = 0;
        added = func_00187920(body, 1, D_001ED1C0, 8, 0, 9, 8, 0, 0, 0, 0, 1);

        /* Patch the GIF tag in front of the block that was just written:
         * NREG = 1, REGS0 = A+D (0xE), NLOOP = qwords written. */
        gif = (long *)p;
        gif[0] = (gif[0] & 0x0FFFFFFFFFFFFFFFL) | 0x1000000000000000L;
        gif[1] = (gif[1] & ~0xFL) | 0xEL;
        gif[0] = (gif[0] & ~0x7FFFL) | (added & 0x7FFF);

        /* Fourth A+D pair holds CLAMP: WMS/WMT = 0, MINU/MINV = 0,
         * MAXU = 0x200, MAXV = 0xE0. */
        *(long *)(body + 0x30) = *(long *)(body + 0x30) & ~3L;
        *(long *)(body + 0x30) = *(long *)(body + 0x30) & ~0xCL;
        *(long *)(body + 0x30) = *(long *)(body + 0x30) & ~0x3FF0L;
        *(long *)(body + 0x30) = (*(long *)(body + 0x30) & ~0xFFC000L) | 0x800000L;
        *(long *)(body + 0x30) = *(long *)(body + 0x30) & ~0x3FF000000L;
        *(long *)(body + 0x30) = (*(long *)(body + 0x30) & ~0xFFC00000000L) | 0x38000000000L;
        p += added * 16 + 0x10;

        written = qwords + 1;
        qwords = written + added;

        added = func_00113648(p, 0x42,
                              ((long)((D_001ED1C4 << 7) / D_001EC8B8) << 32) | 0x64);
        p += added * 16;
        qwords += added;

        added = func_00113648(p, 0x47, 0x31001);
        p += added * 16;
        qwords += added;

        added = func_00113670(p, -0x100, -0xE0, 0x100, 0xE0, 0, 0, 0x1FF0,
                              0xDF0, 0xFFFFFF, 0x80808080);
        p += added * 16;
        qwords += added;

        added = func_00113648(p, 0x42, 0x8000000044L);
        p += added * 16;
        qwords += added;

        added = func_00113648(p, 0x47, 0x7001B);
        p += added * 16;
        qwords += added;

        D_001ED1C4 = D_001ED1C4 - 1;
    } else if (D_001ED1C0 != 0) {
        func_0017E9B0(D_001ED1C0);
        D_001ED1C0 = 0;
    }

    /* Terminating GIF tag: NLOOP = 0, EOP = 1. */
    qwords = qwords + 1;
    *(long *)p = 0x8000;
    *(short *)chain = qwords;
    return qwords + 1;
}
