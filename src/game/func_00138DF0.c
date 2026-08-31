typedef struct Entry36 {
    unsigned char bytes[36];
} Entry36;

extern unsigned char D_00203C34[];

Entry36 *func_00138DF0(int index) {
    return (Entry36 *)(D_00203C34 + index * 36);
}
