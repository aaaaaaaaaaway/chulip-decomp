typedef struct {
    unsigned int start;
    int end;
} Entry;

typedef struct {
    unsigned short start;
    unsigned short end;
    unsigned short unknown;
} Gap;

extern unsigned int D_001ECF94;
extern Entry D_002DB100[];
void func_0017E468(unsigned int, int);

unsigned int func_0017E840(unsigned int size, unsigned char from_end) {
    Gap gaps[128];
    int count = 0;
    int cursor = 0x1e00;
    int limit = 0x4000;
    int i;
    int selected;
    unsigned int result;
    for (i = 0; i < D_001ECF94; ++i) {
        if (cursor != D_002DB100[i].start) {
            gaps[count].start = cursor;
            gaps[count].end = D_002DB100[i].start;
            ++count;
        }
        cursor = (unsigned short)D_002DB100[i].end;
    }
    if (cursor != limit) {
        gaps[count].start = cursor;
        gaps[count].end = limit;
        ++count;
    }
    size >>= 6;
    selected = -1;
    for (i = 0; i < count; ++i) {
        if (size < (unsigned short)(gaps[i].end - gaps[i].start)) {
            selected = i;
            break;
        }
    }
    if (from_end) {
        func_0017E468(gaps[selected].end - size, gaps[selected].end);
        result = gaps[selected].end - size;
    } else {
        func_0017E468(gaps[selected].start, gaps[selected].start + size);
        result = gaps[selected].start;
    }
    return result;
}
