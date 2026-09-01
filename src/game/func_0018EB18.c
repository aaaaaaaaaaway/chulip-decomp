typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
} ThreadParam;

extern void func_0018EAF0(void);
extern int func_001987A0(ThreadParam *param);
extern void func_00198520(int index, void (*handler)(void), int arg);
extern void func_001987E0(int id);
extern void func_001987B0(int id);

void func_0018EB18(int id) {
    ThreadParam param;
    int index;
    int handle;

    index = id & 0xFFFF;
    param.unk4 = 1;
    param.unk8 = 0;
    param.unk14 = 0;
    handle = func_001987A0(&param);
    func_00198520(index, func_0018EAF0, handle);
    func_001987E0(handle);
    func_001987B0(handle);
}
