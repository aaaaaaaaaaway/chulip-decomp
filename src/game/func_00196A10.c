/* newlib _fwalk: apply a function to every open FILE of a reent. */
typedef struct {
    char pad0[0xC];
    short flags;
    char pad0E[0x4A];
} File;

typedef struct Glue {
    struct Glue *next;
    int niobs;
    File *iobs;
} Glue;

typedef struct {
    char pad0[0x1D8];
    Glue glue;
} Reent;

int func_00196A10(Reent *reent, int (*function)(File *)) {
    File *fp;
    int n;
    int ret;
    Glue *g;

    ret = 0;
    for (g = &reent->glue; g != 0; g = g->next) {
        for (fp = g->iobs, n = g->niobs; --n >= 0; fp++) {
            if (fp->flags != 0) {
                ret |= function(fp);
            }
        }
    }
    return ret;
}
