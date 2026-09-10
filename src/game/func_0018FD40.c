/* Set the CDVD media mode through synchronous command 0x22. */
typedef struct {
    int fields[9];
    void *server;
} Client;
extern int func_0019B760(Client *, int, int, void *, int, void *, int, void *, void *);
extern int func_001987C0(int);
extern void func_0019AE70(void *, int);
extern Client D_001E4B88;
extern int D_001E4780[], D_001E4340[], D_001E316C[];
extern int func_0018F6F8(int);
int func_0018FD40(int mode) {
    int *send = D_001E4780;
    int result;
    if (!func_0018F6F8(0x22))
        return 0;
    D_001E4780[0] = mode;
    func_0019AE70(send, 4);
    if (func_0019B760(&D_001E4B88, 0x22, 0, send, 4, D_001E4340, 4, 0, 0) < 0) {
        func_001987C0(D_001E316C[0]);
        return 0;
    }
    result = *(int *)((unsigned int)D_001E4340 | 0x20000000);
    func_001987C0(D_001E316C[0]);
    return result;
}
