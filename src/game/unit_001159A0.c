struct S8_char { char a; char pad[7]; };

typedef struct PacketHeader {
    unsigned long tag;
    unsigned long register_count;
    unsigned long second_value;
    unsigned long first_value;
} PacketHeader;

extern char D_001ED1E1;

void func_00116F90();

void func_00117138();

int func_00112EB0();

extern char D_001ED1DC;

extern struct S8_char D_001ED1DD;

void func_00115F18();

void func_00116438();

void func_00116AE8();

void func_00117360();

int func_001159A0(void) {
    D_001ED1E1 = 0;
    func_00112EB0(func_00116F90, 0, 0);
    return func_00112EB0(func_00117138, 0, 0);
}

int func_001159E0(void) {
    D_001ED1DD.a = 0;
    D_001ED1DC = 0;
    func_00112EB0(func_00115F18, 0, 0);
    func_00112EB0(func_00116438, 0, 0);
    func_00112EB0(func_00116AE8, 0, 0);
    return func_00112EB0(func_00117360, 0, 0);
}

int func_00115A50(PacketHeader *packet, unsigned long first, unsigned long second) {
    packet->tag = 0x1000000000008001UL;
    packet->register_count = 14;
    packet->second_value = second;
    packet->first_value = first;
    return 2;
}
