typedef struct {
    unsigned short owner, first, second, target, part;
} Relation;
extern Relation D_002D4800[];
void *func_001548A0(unsigned short);
void func_001585A8(unsigned short, unsigned short, unsigned char);

void func_00158250(unsigned short owner, unsigned short first, unsigned short second,
                   unsigned short target, unsigned short part, unsigned char enable) {
    int i, j;
    if (enable) {
        func_001548A0(owner);
        func_001548A0(target);
        for (i = 0; i < 16; ++i) {
            if (D_002D4800[i].owner == owner && D_002D4800[i].target == target &&
                D_002D4800[i].part == part) {
                D_002D4800[i].first = first;
                D_002D4800[i].second = second;
                return;
            }
            if (D_002D4800[i].owner == 0xffff) {
                D_002D4800[i].owner = owner;
                D_002D4800[i].first = first;
                D_002D4800[i].second = second;
                D_002D4800[i].target = target;
                D_002D4800[i].part = part;
                func_001585A8(owner, 0x800, 1);
                func_001585A8(target, 0x1000, 1);
                return;
            }
        }
    } else {
        for (i = 0; i < 16; ++i) {
            if (D_002D4800[i].owner == owner) {
                for (j = 0; j < 16; ++j) {
                    if (i != j && D_002D4800[j].owner != 0xffff &&
                        D_002D4800[j].target == D_002D4800[i].target)
                        break;
                }
                if (j >= 16)
                    func_001585A8(target, 0x1000, 0);
                D_002D4800[i].owner = 0xffff;
                D_002D4800[i].first = 0xffff;
                D_002D4800[i].second = 0xffff;
                D_002D4800[i].target = 0xffff;
                D_002D4800[i].part = 0xffff;
                func_001585A8(owner, 0x800, 0);
                func_001585A8(owner, 2, 0);
                return;
            }
        }
    }
}
