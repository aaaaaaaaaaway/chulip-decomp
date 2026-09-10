typedef struct Packet {
    unsigned int header[4];
    int record_id;
    void *self;
    int rpc_id;
} Packet;
typedef struct {
    Packet *packet;
    int rpc_id, semaphore, mode;
} ClientHeader;
int func_0019B950(ClientHeader *client) {
    Packet *packet = client->packet;
    if (!packet || client->rpc_id != packet->rpc_id || !(packet->record_id & 1))
        return 0;
    return 1;
}
