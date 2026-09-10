/* Module-buffer-load RPC reconstruction. Protocol fields follow the loadfile
   interface; control flow and shared packet use follow retail. */
typedef struct {
    union {
        int result;
        void *buffer;
    } p;
    int argument_length;
    /* Reserved pathname slot in the shared loadfile RPC protocol. */
    char reserved[252];
    char arguments[252];
} ModuleRequest;

extern ModuleRequest D_002E3E80;
extern unsigned char D_002E4080[];
extern int func_0019F818(void);
extern int func_0019F918(void);
extern void *func_00192344(void *, const void *, unsigned int);
extern int func_0019B760(void *, int, int, void *, int, void *, int, void (*)(void *), void *);

int func_0019F9E0(void *buffer, int argument_length, const char *arguments, int *module_result) {
    int result;

    if (func_0019F818() < 0)
        return -65536;
    if (func_0019F918())
        return -65540;
    D_002E3E80.p.buffer = buffer;
    if (arguments) {
        if (argument_length > 252) {
            __builtin_memcpy(D_002E3E80.arguments, arguments, 252);
            D_002E3E80.argument_length = 252;
        } else {
            func_00192344(D_002E3E80.arguments, arguments, argument_length);
            D_002E3E80.argument_length = argument_length;
        }
    } else {
        D_002E3E80.argument_length = 0;
    }
    if (func_0019B760(D_002E4080, 6, 0, &D_002E3E80, 512, &D_002E3E80, 8, 0, 0) < 0)
        return -65537;
    result = D_002E3E80.p.result;
    *module_result = D_002E3E80.argument_length;
    return result;
}
