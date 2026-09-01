extern int D_001ED894;
extern int D_001ED898;
extern int D_001ED89C;
extern int D_001ED8A0;
extern int D_001ED8C4;
extern int D_001ED8C8;
extern int D_001ED8CC;

int func_0012CB20();
int func_0012CB30();
int func_0012CB50();
int func_0017ABE8();
int func_0017ABF8();

void func_0017AB40(int id, int arg1) {
    unsigned char slot;

    slot = id;
    D_001ED89C = arg1;
    D_001ED8A0 = 0;
    D_001ED894 = 0;
    D_001ED898 = id;
    D_001ED8C4 = func_0012CB30(slot);
    D_001ED8C8 = func_0012CB50(slot);
    D_001ED8CC = func_0012CB20();
    func_0017ABE8();
    func_0017ABF8();
}
