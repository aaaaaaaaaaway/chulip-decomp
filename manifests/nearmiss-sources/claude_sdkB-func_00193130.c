struct Context { char pad[0x38]; int initialized; };
struct File { char pad[0x54]; struct Context *context; };
extern struct Context *D_001E4EB4[];
extern void func_00196118(struct Context *context);
extern int func_001931A8(struct Context *context, struct File *file, int b, int c);

int func_00193130(struct File *file, int b, int c) {
    struct Context *context = file->context;
    if (context == 0) {
        context = D_001E4EB4[0];
        file->context = context;
    }
    if (context->initialized == 0) {
        func_00196118(context);
    }
    return func_001931A8(file->context, file, b, c);
}
