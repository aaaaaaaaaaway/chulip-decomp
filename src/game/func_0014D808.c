struct Rec1F0 { char data[0x1F0]; };

extern struct Rec1F0 *D_001ECAC0;
extern unsigned short D_001ECB0C;
extern unsigned short D_001ECB0E;

struct Rec1F0 *func_0014D808(int index, unsigned char wrapped) {
    if (wrapped == 0) {
        return D_001ECAC0 + index;
    }
    return D_001ECAC0 + (index / D_001ECB0C + index % D_001ECB0C * D_001ECB0E);
}
