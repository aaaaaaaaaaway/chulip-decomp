/* Loadfile module RPC with shared request/reply packet. */
typedef struct {
    int argument_length;
    int module_result;
    char path[252];
    char arguments[252];
} ModuleRequest;

extern ModuleRequest D_002E3E80;
extern unsigned char D_002E4080[];
extern int func_0019F818(void);
extern int func_0019F918(void);
extern char *func_00192B90(char *, const char *, unsigned int);
extern void *func_00192344(void *, const void *, unsigned int);
extern int func_0019B760(void *, int, int, void *, int, void *, int, void (*)(void *), void *);

int func_0019FFF0(const char *path, int argument_length, const char *arguments, int *module_result,
                  int command) {
    int result;

    if (func_0019F818() < 0)
        return -65536;
    if (func_0019F918())
        return -65540;
    func_00192B90(D_002E3E80.path, path, 252);
    D_002E3E80.path[251] = 0;
    if (arguments) {
        if (argument_length > 252) {
            __builtin_memcpy(D_002E3E80.arguments, arguments, 252);
            D_002E3E80.argument_length = 252;
        } else {
            func_00192344(D_002E3E80.arguments, arguments, argument_length);
            D_002E3E80.argument_length = argument_length;
        }
    } else {
        D_002E3E80.arguments[0] = 0;
        D_002E3E80.argument_length = 0;
    }
    if (func_0019B760(D_002E4080, command, 0, &D_002E3E80, 512, &D_002E3E80, 8, 0, 0) < 0)
        return -65537;
    result = D_002E3E80.argument_length;
    *module_result = D_002E3E80.module_result;
    return result;
}
