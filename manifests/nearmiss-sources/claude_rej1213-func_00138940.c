/* object_flags: -Wa,-G4 */
struct Node_00138940 { short next; unsigned char pad_0x2[0x22]; };

struct Head_00203C08 { short index; short pad[3]; };

extern struct Head_00203C08 D_00203C08;
extern struct Node_00138940 D_00203C3C[];

int func_00138940(void) {
    short index = D_00203C08.index;
    int count = 0;

    while (index != -1) {
        index = D_00203C3C[index].next;
        count++;
    }
    return count;
}
