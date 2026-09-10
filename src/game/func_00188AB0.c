typedef union {
    unsigned int word;
    struct {
        unsigned int direction : 1;
        unsigned int reserved1 : 1;
        unsigned int mode : 2;
        unsigned int reserved4 : 4;
        unsigned int running : 1;
        unsigned int reserved9 : 23;
    } bits;
} ChannelControl;

typedef struct {
    volatile unsigned int control;
    unsigned int reserved04[3];
    unsigned int address;
    unsigned int reserved14[3];
    unsigned int count;
    unsigned int reserved24[3];
    unsigned int tag_address;
} DmaChannel;

extern char D_001EAFB0[];
extern int func_00192508(const char *format, ...);

void func_00188AB0(DmaChannel *channel, unsigned int address, unsigned int count)
{
    ChannelControl control, command;
    int timeout = 0x1000000;
    while (channel->control & 0x100) {
        if (--timeout < 0) {
            func_00192508(D_001EAFB0);
            control.word = channel->control;
            if (control.bits.running) {
                ChannelControl stopped;
                while (control.bits.running) {
                    stopped = control;
                    stopped.bits.running = 0;
                    control = stopped;
                }
                channel->control = stopped.word;
            }
        }
    }
    if (channel->address != 0xFFFFFFFF) {
        channel->address = address;
    }
    channel->count = count;
    command.word = channel->control;
    command.bits.mode = 2;
    command.bits.direction = 1;
    command.bits.running = 1;
    channel->control = command.word;
}
