typedef struct SifCmdHeader {
    int psize;
    int dsize;
    int dest;
    int cid;
} SifCmdHeader;

typedef struct SifRpcHeader {
    int pkt_addr;
    int rpc_id;
    int sema_id;
    unsigned int mode;
} SifRpcHeader;

typedef struct SifRpcClientData {
    SifRpcHeader hdr;
    int command;
    int buff;
    int cbuff;
    int end_function;
    int end_param;
    int server;
} SifRpcClientData;

typedef struct SifRpcCallPkt {
    SifCmdHeader sifcmd;
    int rec_id;
    int pkt_addr;
    int rpc_id;
    int client;
    int rpc_number;
    int send_size;
    int receive;
    int recv_size;
    int rmode;
    int server;
} SifRpcCallPkt;

typedef struct ee_sema {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    int attr;
    int option;
} ee_sema_t;

extern int D_002E28C0[];

extern SifRpcCallPkt *func_0019B0E8(void *pool);
extern void func_0019B190(SifRpcCallPkt *packet);
extern void func_0019AE70(void *addr, int size);
extern int func_0019ACC8(int cmd, void *packet, int size, void *src, void *dest, int esize);
extern int func_001987A0(ee_sema_t *sema);
extern void func_001987B0(int id);
extern void func_001987E0(int id);

int func_0019B760(SifRpcClientData *client, unsigned int rpc_number, unsigned int mode,
                  void *sendbuf, int ssize, void *recvbuf, int rsize,
                  void (*end_function)(void *), void *end_param)
{
    ee_sema_t sema;
    SifRpcCallPkt *packet;

    packet = func_0019B0E8(D_002E28C0);
    if (packet == 0) {
        return -1;
    }
    client->hdr.rpc_id = packet->rpc_id;
    client->hdr.pkt_addr = (int)packet;
    client->end_param = (int)end_param;
    client->end_function = (int)end_function;
    packet->rpc_number = rpc_number;
    packet->send_size = ssize;
    packet->receive = (int)recvbuf;
    packet->recv_size = rsize;
    packet->pkt_addr = (int)packet;
    packet->server = client->server;
    packet->client = (int)client;

    if ((mode & 2) == 0) {
        if (sendbuf == recvbuf) {
            func_0019AE70(sendbuf, ssize < rsize ? rsize : ssize);
        } else {
            if (ssize > 0) {
                func_0019AE70(sendbuf, ssize);
            }
            if (rsize > 0) {
                func_0019AE70(recvbuf, rsize);
            }
        }
    }
    if ((mode & 1) != 0) {
        if (end_function == 0) {
            packet->rmode = 0;
        } else {
            packet->rmode = 1;
        }
        client->hdr.sema_id = -1;
        if (func_0019ACC8(0x8000000A, packet, 0x40, sendbuf, (void *)client->buff, ssize) == 0) {
            func_0019B190(packet);
            return -2;
        }
    } else {
        sema.init_count = 0;
        sema.max_count = 1;
        client->hdr.sema_id = func_001987A0(&sema);
        if (client->hdr.sema_id < 0) {
            func_0019B190(packet);
            return -3;
        }
        packet->rmode = 1;
        if (func_0019ACC8(0x8000000A, packet, 0x40, sendbuf, (void *)client->buff, ssize) == 0) {
            func_001987B0(client->hdr.sema_id);
            func_0019B190(packet);
            return -2;
        }
        func_001987E0(client->hdr.sema_id);
        func_001987B0(client->hdr.sema_id);
    }
    return 0;
}
