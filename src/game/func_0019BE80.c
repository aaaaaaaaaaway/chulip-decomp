struct Request { int f0; int f4; int f8; int fC; int f10; int f14; };
extern int D_001E5B88[];
extern int D_001E5B8C[];
extern int func_001987A0(struct Request *request);

void func_0019BE80(void) {
    struct Request request;
    if (D_001E5B88[0] == -1) {
        request.f14 = 0;
        request.f8 = 1;
        request.f4 = 1;
        D_001E5B88[0] = func_001987A0(&request);
        D_001E5B8C[0] = func_001987A0(&request);
    }
}
