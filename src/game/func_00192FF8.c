struct _reent;
extern struct _reent *D_001E4EB4;
extern long func_00192DC0(struct _reent *context, const char *text, char **end, int base);

long func_00192FF8(const char *text, char **end, int base) {
    return func_00192DC0(D_001E4EB4, text, end, base);
}
