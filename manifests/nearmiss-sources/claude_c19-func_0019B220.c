typedef struct Client {
    int f0; int f4; int sema; int fC; int f10;
    int f14; int f18;
    void (*endf)(void *);
    void *endp;
    int server;
} Client;
typedef struct {
    int h0; int h4; int h8; int hC; int h10; int h14; int h18;
    Client *client;
    unsigned int cmd;
    int f24; int f28; int f2C;
} RendPkt;

extern void func_001987D0(int sema);
extern void func_0019B190(int pkt);

void func_0019B220(RendPkt *pkt) {
    Client *c;

    switch (pkt->cmd) {
    case 0x8000000A:
        c = pkt->client;
        if (c->endf != 0) {
            c->endf(c->endp);
        }
        c = pkt->client;
        break;
    case 0x80000009:
        c = pkt->client;
        c->server = pkt->f24;
        c->f14 = pkt->f28;
        c->f18 = pkt->f2C;
        break;
    default:
        c = pkt->client;
        break;
    }
    if (c->sema >= 0) {
        func_001987D0(c->sema);
    }
    func_0019B190(c->f0);
    c->f0 = 0;
}
