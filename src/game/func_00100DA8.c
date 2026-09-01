typedef struct { float a[4]; float b[4]; float c[4]; int d[4]; } Mat;
typedef struct { int f0; Mat *f4; int f8; int fC; unsigned int f10; } Node;

void func_00100DA8(Node *dst, Node *src) {
    unsigned int i;
    unsigned int j;
    int id;
    Mat *m;
    i = 0;
    if (src->f10 != 0) {
        do {
            id = *(int *)(i * 16 + src->f0);
            m = src->f4 + id; j = m->d[0] == -1;
            for (; j < 4; j++) { dst->f4[id].a[j] = src->f4[id].a[j]; }
            for (j = 0; j < 4; j++) { dst->f4[id].b[j] = src->f4[id].b[j]; }
            i++;
        } while (i < src->f10);
    }
}
