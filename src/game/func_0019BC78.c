/* Execute a registered RPC request and deliver its completion packet. */
typedef struct {
    unsigned int command;
    void *(*function)(int command, void *buffer, int size);
    void *buffer;
    int size;
    void *callback;
    void *callback_buffer;
    int callback_size;
    struct RpcClient *client;
    void *packet_address;
    int rpc_number;
    void *receive_buffer;
    int receive_size;
    int receive_mode;
    unsigned int request_id;
} Server;
typedef struct {
    unsigned int header[4];
    int record_id;
    void *packet_address;
    int rpc_id;
    struct RpcClient *client;
    unsigned int command;
} Completion;
/* DMA descriptors carry 32-bit EE addresses, not host-sized pointers. */
typedef struct {
    unsigned int source;
    unsigned int destination;
    int size;
    int attributes;
} DmaTransfer;
extern unsigned char D_002E28C0[];
extern void func_0019AE70(void *address, int size);
/* Both interrupt helpers return the previous interrupt-enable flag. */
extern int func_001A0828(void);
extern int func_001A0870(void);
extern Completion *func_0019B1E0(void *state, int id);
extern Completion *func_0019B1B0(void *state);
extern int func_0019ACC8(unsigned int command, void *packet, int packet_size, void *source,
                         void *destination, int size);
extern int func_00198B60(DmaTransfer *transfers, int count);

void func_0019BC78(Server *server) {
    void *reply;
    int reply_size = 0;
    Completion *completion;
    DmaTransfer transfers[2];
    int count;
    int dma_id;
    int delay;

    reply = server->function(server->rpc_number, server->buffer, server->size);
    if (reply != 0)
        reply_size = server->receive_size;
    if (server->size > 0)
        func_0019AE70(server->buffer, server->size);
    if (reply_size > 0)
        func_0019AE70(reply, reply_size);
    func_001A0828();
    if (server->request_id & 4)
        completion = func_0019B1E0(D_002E28C0, server->request_id >> 16);
    else
        completion = func_0019B1B0(D_002E28C0);
    func_001A0870();
    completion->client = server->client;
    completion->command = 0x8000000A;
    if (server->receive_mode) {
        while (
            !func_0019ACC8(0x80000008, completion, 64, reply, server->receive_buffer, reply_size)) {
        }
    } else {
        completion->rpc_id = 0;
        completion->record_id = 0;
        count = 0;
        if (reply_size > 0) {
            transfers[count].source = (unsigned int)reply;
            transfers[count].destination = (unsigned int)server->receive_buffer;
            transfers[count].size = reply_size;
            transfers[count].attributes = 0;
            count++;
        }
        transfers[count].source = (unsigned int)completion;
        transfers[count].destination = (unsigned int)server->packet_address;
        transfers[count].size = 64;
        transfers[count].attributes = 0;
        count++;
        do {
            dma_id = func_00198B60(transfers, count);
            if (dma_id == 0) {
                for (delay = 0x100000; delay != -1; --delay) {
                }
            }
        } while (dma_id == 0);
    }
}
