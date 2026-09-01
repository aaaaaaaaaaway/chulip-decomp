typedef struct Bigint {
    struct Bigint *_next;
    int _k;
    int _maxwds;
    int _sign;
    int _wds;
    unsigned int _x[1];
} Bigint;

typedef struct Reent Reent;

extern int D_001EBFD0[];
extern Bigint *func_00196FE0(Reent *ptr, Bigint *b, int m, int a);
extern Bigint *func_00197388(Reent *ptr, int i);
extern Bigint *func_001973C0(Reent *ptr, Bigint *a, Bigint *b);
extern void func_00196FB0(Reent *ptr, Bigint *b);

struct ReentP5 { char pad[0x48]; Bigint *_p5s; };

Bigint *func_001975F0(Reent *ptr, Bigint *b, int k) {
    Bigint *b1;
    Bigint *p5;
    Bigint *p51;
    int i;

    i = k & 3;
    if (i != 0) {
        b = func_00196FE0(ptr, b, D_001EBFD0[i - 1], 0);
    }
    k >>= 2;
    if (k == 0) {
        return b;
    }
    p5 = ((struct ReentP5 *)ptr)->_p5s;
    if (p5 == 0) {
        p5 = ((struct ReentP5 *)ptr)->_p5s = func_00197388(ptr, 625);
        p5->_next = 0;
    }
    for (;;) {
        if ((k & 1) != 0) {
            b1 = func_001973C0(ptr, b, p5);
            func_00196FB0(ptr, b);
            b = b1;
        }
        k >>= 1;
        if (k == 0) {
            break;
        }
        p51 = p5->_next;
        if (p51 == 0) {
            p51 = func_001973C0(ptr, p5, p5);
            p5->_next = p51;
            p51->_next = 0;
        }
        p5 = p51;
    }
    return b;
}
