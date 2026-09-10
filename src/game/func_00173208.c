/* Apply object-list operations to entries selected by flags or kind. */
struct State { unsigned char pad[16]; unsigned short count; };
struct Entry { unsigned int flags; unsigned char pad[106]; unsigned short kind; unsigned char rest[80]; };
extern struct State D_002D8840;
extern int D_001ED6C0;
void func_00173208(unsigned short bits, unsigned char set) {
 int i;
 for(i=0; i<D_002D8840.count;i++) {
 if(set) (*(unsigned int *)(D_001ED6C0 + i * 0xC0)) |= bits;
 else (*(unsigned int *)(D_001ED6C0 + i * 0xC0)) &= ~bits;
 }
}
