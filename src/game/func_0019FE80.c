typedef struct {
    int result;
    int unk4;
    char name[0x100];
} Request;

extern Request D_002E3E80;
extern int D_002E4080[];
extern int func_0019F818(void);
extern int func_0019F918(void);
extern char *func_00192B90(char *dst, const char *src, int size);
extern int func_0019B760(int *name, int a, int b, int *in, int inlen,
                         int *out, int outlen, int f, int g);

int func_0019FE80(const char *name) {
    if (func_0019F818() < 0) {
        return 0xFFFF0000;
    }
    if (func_0019F918() != 0) {
        return 0xFFFEFFFC;
    }
    func_00192B90(D_002E3E80.name, name, 0xFC);
    D_002E3E80.name[0xFB] = 0;
    if (func_0019B760(D_002E4080, 9, 0, (int *)&D_002E3E80, 0x200,
                      (int *)&D_002E3E80, 4, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    return D_002E3E80.result;
}
