/* newlib __sinit */
typedef struct {
    char pad0[0x58];
} File;

typedef struct Reent {
    char pad0[0x38];
    int didinit;
    void (*cleanup)(struct Reent *);
    char pad40[0x198];
    struct Glue {
        void *next;
        int niobs;
        File *iobs;
    } glue;
    File sf[3];
} Reent;

extern void func_001960F8(struct Reent *reent);
extern void func_00195F50(File *fp, int flags, int file, Reent *reent);

void func_00196118(Reent *reent) {
    reent->cleanup = func_001960F8;
    reent->didinit = 1;
    func_00195F50(&reent->sf[0], 4, 0, reent);
    func_00195F50(&reent->sf[1], 9, 1, reent);
    func_00195F50(&reent->sf[2], 0xA, 2, reent);
    reent->glue.iobs = &reent->sf[0];
    reent->glue.niobs = 3;
    reent->glue.next = 0;
}
