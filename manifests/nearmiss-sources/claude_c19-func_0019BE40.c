extern void *func_0019BC20(int arg);
extern void func_0019BC78(void *pkt);
extern void func_001986C0(void);

void func_0019BE40(int arg) {
    void *pkt;

    goto top;
again:
    func_0019BC78(pkt);
top:
    pkt = func_0019BC20(arg);
    if (pkt != 0) {
        goto again;
    }
    func_001986C0();
    goto top;
}
