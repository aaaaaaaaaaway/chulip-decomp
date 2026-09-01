typedef struct {
    float x;
    float y;
    float z;
    float w;
} Key;

extern int D_001ED230;
extern int D_001ED234;
extern Key *D_001ED238;
extern Key *D_001ED23C;

void func_0011FC68(void);
void func_00112F40(void *entry);
void func_00112EB0(void *entry, int arg, int order);

void func_0011FB50(Key *first, Key *second) {
    D_001ED238 = first;
    D_001ED234 = 1;
    D_001ED23C = second;
    D_001ED230 = 0;
    if (first != 0 || second != 0) {
        if (first->w != -1000.0f && second->w != -1000.0f) {
            do {
                D_001ED230 = D_001ED230 + 1;
            } while (first[D_001ED230].w != -1000.0f &&
                     second[D_001ED230].w != -1000.0f);
        }
    }
    func_00112F40(func_0011FC68);
    func_00112EB0(func_0011FC68, 0, 0);
}
