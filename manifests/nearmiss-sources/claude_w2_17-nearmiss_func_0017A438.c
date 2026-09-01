typedef struct {
    char pad00[0xC];
    unsigned int count;
} Hdr0017A438;

char *func_0017A438(int unused, Hdr0017A438 *hdr, unsigned int index) {
    unsigned int count;
    unsigned int n0;
    unsigned int n1;
    unsigned int i;
    char *p;

    count = hdr->count;
    i = 0;
    p = (char *)hdr + 0x10;
    if (count != 0) {
        if (index != 0) {
            do {
                p += 0x10;
                n0 = *(unsigned int *)p;
                n1 = *(unsigned int *)(p + 4);
                p += 0x10;
                p += n0 * 4;
                p += n1 * 4;
                i++;
                if (i >= count) {
                    return 0;
                }
            } while (index != i);
        }
        return p;
    }
    return 0;
}
