/* Reset the GS drawing engine and select the display timing mode. */
typedef unsigned long Register64;
typedef struct {
    short interlace, video_mode, frame_mode;
    unsigned short revision;
    int interrupt_enabled, interrupt_handler;
} DisplayInfo;
extern DisplayInfo *func_00187498(void);
extern Register64 func_00198AE0(Register64 mask);
extern int func_00199280(int interrupt);
extern int func_001984A0(int interrupt, int handler);
extern void func_001983A0(short interlace, short mode, short field);
void func_00187308(short mode, short interlace, short video_mode, short frame_mode) {
    DisplayInfo *info;
    switch (mode) {
    case 0:
        info = func_00187498();
        *(volatile Register64 *)0x12001000 = 0x200;
        info->interlace = interlace;
        info->video_mode = video_mode;
        info->revision = (*(volatile Register64 *)0x12001000 >> 16) & 0xFF;
        func_00198AE0(0xFF00);
        info->frame_mode = frame_mode != 0;
        if (info->interrupt_enabled) {
            func_00199280(2);
            func_001984A0(2, info->interrupt_handler);
            info->interrupt_enabled = 0;
            info->interrupt_handler = 0;
        }
        func_001983A0(interlace & 1, video_mode & 0xFF, frame_mode & 1);
        break;
    case 1:
        *(volatile Register64 *)0x12001000 = 0x100;
        break;
    case 5:
        info = func_00187498();
        info->interlace = interlace;
        info->video_mode = video_mode;
        info->revision = (*(volatile Register64 *)0x12001000 >> 16) & 0xFF;
        info->frame_mode = frame_mode != 0;
        func_001983A0(interlace & 1, video_mode & 0xFF, frame_mode & 1);
        break;
    }
}
