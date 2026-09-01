extern int D_001ED364;
extern int D_001ED368[];
extern char D_001FEFF0[][0x20];
extern char D_001EC990[];
extern char D_001EC998[];
extern char D_001EC9A0[];
extern char *D_001FF050[];
extern int D_001FF060[];

extern unsigned char *func_0012CB20(void);
extern int func_00135430(void);
extern void func_00192660(char *, char *);
extern int func_0012CC18(int, int, int, unsigned char *);
extern void func_00135670(int, char **);
extern void func_001353E0(void);
extern int func_001357B8(void);
extern void func_001357A8(void);
extern void func_00135420(void);
extern void func_00134EB8(void);
extern void func_00112F40(void *);

int func_00135020(void);

int func_00135020(void) {
    unsigned char *records;
    int entry;
    int count;
    int i;
    int flags;
    int masks[3];
    int *slots;

    count = 0;
    records = func_0012CB20();
    switch (D_001ED364) {
    case 0:
        entry = func_00135430();
        D_001ED368[D_001ED364] = entry;
        slots = D_001ED368;
        if (entry == -0xFF) {
            D_001ED364 = 2;
            break;
        }
        if (entry < 0) {
            break;
        }
        func_00192660(D_001FEFF0[0], D_001EC990);
        func_00192660(D_001FEFF0[1], D_001EC998);
        func_00192660(D_001FEFF0[2], D_001EC9A0);
        masks[0] = 1;
        masks[1] = 8;
        masks[2] = 0x10;
        flags = func_0012CC18((records + entry)[2], 4, 0, records + entry);
        for (i = 0; i < 3; i++) {
            D_001FF060[i] = -1;
            if ((flags & masks[i]) == 0) {
                D_001FF050[count] = D_001FEFF0[i];
                D_001FF060[count] = i;
                count++;
            }
        }
        if (count > 0) {
            func_00135670(count, D_001FF050);
            D_001ED364 = 1;
            break;
        }
        func_001353E0();
        slots[D_001ED364] = -1;
        break;
    case 1:
        entry = func_001357B8();
        D_001ED368[D_001ED364] = entry;
        if (entry == -0xFF) {
            D_001ED364 = 0;
            func_001353E0();
            func_001357A8();
            break;
        }
        if (entry < 0) {
            break;
        }
        D_001ED368[D_001ED364] = D_001FF060[entry];
        D_001ED364 = 2;
        break;
    case 2:
        D_001ED364 = 2;
        func_00135420();
        func_001357A8();
        func_00134EB8();
        break;
    case 3:
        func_00112F40(func_00135020);
        break;
    }
    return 0;
}
