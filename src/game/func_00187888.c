typedef struct DisplayInfo {
    short interlace;
    short field2;
    short field4;
    short mode;
    int use_saved_status;
} DisplayInfo;
extern DisplayInfo *func_00187498(void);
extern void func_00198C30(void);
extern long func_00198CC0(void);
#define GS_CSR (*(volatile unsigned long *)0x12001000)
int func_00187888(void) {
    DisplayInfo *info = func_00187498();
    if (info->use_saved_status == 0) {
        func_00198C30();
        if (info->interlace == 1)
            return (GS_CSR >> 13) & 1;
    } else {
        long field = (func_00198CC0() >> 13) & 1;
        if (info->interlace == 1)
            return field;
    }
    return 1;
}
