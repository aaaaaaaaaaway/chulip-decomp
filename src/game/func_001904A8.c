typedef struct {
    int n0;
    int n1;
    char *d0;
    char *d1;
    char b0[0x40];
    char b1[0x40];
} M;
void func_001904A8(unsigned int addr)
{
    M *m = (M *)(addr | 0x20000000);
    char *d;
    int i;

    if (m->n0 != 0) {
        d = m->d0;
        for (i = 0; i < m->n0; i++) {
            *d = m->b0[i];
            d++;
        }
    }
    if (m->n1 != 0) {
        d = m->d1;
        for (i = 0; i < m->n1; i++) {
            *d = m->b1[i];
            d++;
        }
    }
}
