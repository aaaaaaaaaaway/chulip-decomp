typedef struct {
    int start0;
    int count0;
    int start1;
    int count1;
} Part0017A9E0;

typedef struct {
    char pad00[0x10];
    void *src0;
    void *src1;
    void *dst0;
    void *dst1;
    char pad20[0x20];
    Part0017A9E0 *parts;
    int count;
    char *mats;
} Skin0017A9E0;

int func_0017AA90();

void func_0017A9E0(Skin0017A9E0 *skin) {
    Part0017A9E0 *part;
    char *mat;
    int i;

    for (i = 0; i < skin->count; i++) {
        part = &skin->parts[i];
        mat = skin->mats + i * 0x90;
        if (part->count0 != 0) {
            func_0017AA90(mat + 0x10, skin->src0, skin->dst0, part->start0, part->count0);
            func_0017AA90(mat + 0x50, skin->src1, skin->dst1, part->start1, part->count1);
        }
    }
}
