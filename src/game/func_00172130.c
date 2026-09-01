typedef struct Rec {
    int value;
    unsigned char pad[0xBC];
} Rec;

extern Rec *D_001ED6C0;

int func_00173148(unsigned short index);

int func_00172130(unsigned short index) {
    return (D_001ED6C0 + func_00173148(index))->value;
}
