/* Apply object-list operations to entries selected by flags or kind. */
struct State { unsigned char pad[16]; unsigned short count; };
struct Entry { unsigned int flags; unsigned char pad[106]; unsigned short kind; unsigned char rest[80]; };
extern struct State D_002D8840;
extern int D_001ED6C0;
extern void func_001715D8(int index);
void func_00171478(int kind) {
 int i;
 for(i=1; i<D_002D8840.count;i++) {
 if (((struct Entry *)D_001ED6C0)[i].kind == kind && ((*(unsigned int *)(D_001ED6C0 + i * 0xC0)) & 0x800000) == 0) func_001715D8(i);
 }
}
