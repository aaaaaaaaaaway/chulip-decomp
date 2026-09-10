/* Send a command packet with an optional preceding payload DMA. */
typedef struct {
    unsigned int packet_size : 8;
    unsigned int data_size : 24;
    void *destination;
    unsigned int command;
    unsigned int option;
} Command;
typedef struct {
    unsigned int source, destination;
    int size, attributes;
} Dma;
extern unsigned int D_002E0F20[];
extern void func_0019AE70(void *, int);
extern int func_00198B60(Dma *, int);
extern int func_00198B70(Dma *, int);
unsigned int func_0019AB90(unsigned int command, int mode, Command *packet, int packet_size,
                           void *source, void *destination, int size) {
    Dma transfers[2];
    int count;
    if (((unsigned int)packet_size - 16) > 96)
        return 0;
    count = 0;
    if (size > 0) {
        packet->data_size = size;
        transfers[count].source = (unsigned int)source;
        transfers[count].destination = (unsigned int)destination;
        packet->destination = destination;
        transfers[count].size = size;
        transfers[count].attributes = 0;
        count++;
        if (mode & 4)
            func_0019AE70(source, size);
    } else {
        packet->data_size = 0;
        packet->destination = 0;
    }
    transfers[count].source = (unsigned int)packet;
    transfers[count].destination = D_002E0F20[0];
    transfers[count].size = packet_size;
    packet->command = command;
    packet->packet_size = packet_size;
    transfers[count].attributes = 0x44;
    count++;
    func_0019AE70(packet, packet_size);
    if (mode & 1)
        return func_00198B70(transfers, count);
    return func_00198B60(transfers, count);
}
