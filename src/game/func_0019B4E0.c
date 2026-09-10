/* Reply to an RPC bind request with the located server's buffers. */
typedef struct Server {
    int command;
    void *(*function)(int, void *, int);
    unsigned int buffer;
    int size;
    void *(*callback)(int, void *, int);
    unsigned int callback_buffer;
} Server;
typedef struct {
    unsigned int header[4];
    int record_id;
    unsigned int packet_address;
    int rpc_id;
    unsigned int client;
    unsigned int server_id;
} BindPacket;
typedef struct {
    unsigned int header[4];
    int record_id;
    unsigned int packet_address;
    int rpc_id;
    unsigned int client;
    unsigned int command;
    unsigned int server;
    unsigned int buffer;
    unsigned int callback_buffer;
} Completion;
extern Completion *func_0019B1B0(void *);
extern Server *func_0019B490(int, void *);
extern int func_0019AD08(unsigned int, void *, int, void *, void *, int);
void func_0019B4E0(BindPacket *request, void *state) {
    Completion *reply = func_0019B1B0(state);
    Server *server;
    {
        unsigned int address = request->packet_address;
        unsigned int client = request->client;
        reply->client = client;
        reply->packet_address = address;
    }
    reply->command = 0x80000009;
    server = func_0019B490(request->server_id, state);
    if (!server) {
        reply->server = 0;
        reply->buffer = 0;
        reply->callback_buffer = 0;
    } else {
        reply->server = (unsigned int)server;
        reply->buffer = (unsigned int)server->buffer;
        reply->callback_buffer = (unsigned int)server->callback_buffer;
    }
    func_0019AD08(0x80000008, reply, 64, 0, 0, 0);
}
