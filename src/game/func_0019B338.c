/* Request an IOP-to-EE copy, synchronously or with polling completion. */
typedef struct {
    void *packet;
    int rpc_id, semaphore, mode;
} Receive;
typedef struct {
    unsigned int header[4];
    int record_id;
    void *packet_address;
    int rpc_id;
    Receive *receive;
    void *source, *destination;
    int size;
} OtherPacket;
typedef struct {
    int count, maximum, initial, waiters, attributes, option;
} Semaphore;
extern unsigned char D_002E28C0[];
extern OtherPacket *func_0019B0E8(void *);
extern void func_0019B190(void *);
extern int func_001987A0(Semaphore *);
extern int func_001987B0(int), func_001987E0(int);
extern int func_0019ACC8(unsigned int, void *, int, void *, void *, int);
int func_0019B338(Receive *receive, void *source, void *destination, int size, int mode) {
    Semaphore semaphore;
    OtherPacket *packet = func_0019B0E8(D_002E28C0);
    if (!packet)
        return -1;
    receive->packet = packet;
    receive->rpc_id = packet->rpc_id;
    packet->source = source;
    packet->destination = destination;
    packet->size = size;
    packet->packet_address = packet;
    packet->receive = receive;
    if (!(mode & 1)) {
        semaphore.maximum = 1;
        semaphore.initial = 0;
        receive->semaphore = func_001987A0(&semaphore);
        if (receive->semaphore < 0) {
            func_0019B190(packet);
            return -3;
        }
        if (!func_0019ACC8(0x8000000C, packet, 64, 0, 0, 0)) {
            func_0019B190(packet);
            func_001987B0(receive->semaphore);
            return -2;
        }
        func_001987E0(receive->semaphore);
        func_001987B0(receive->semaphore);
        return 0;
    }
    receive->semaphore = -1;
    if (!func_0019ACC8(0x8000000C, packet, 64, 0, 0, 0)) {
        func_0019B190(packet);
        return -2;
    }
    return 0;
}
