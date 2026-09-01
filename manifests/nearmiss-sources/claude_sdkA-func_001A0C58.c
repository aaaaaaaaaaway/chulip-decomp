typedef struct {
    int command;
    int unk4;
    int unk8;
    void *buffer;
} Request;

extern int D_002E4128[];
extern void func_00198BD0(int channel, Request *request);

void func_001A0C58(unsigned short command, int arg1, int arg2) {
    Request request;

    request.unk4 = arg1;
    request.command = command;
    request.unk8 = arg2;
    request.buffer = (void *)((unsigned int)D_002E4128 | 0x20000000);
    func_00198BD0(1, &request);
}
