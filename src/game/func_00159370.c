typedef struct {
    int unk00;
    int unk04;
    int unk08;
    int unk0C;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    int unk20;
} Template;

typedef struct {
    Template *source;
    int unk04;
    int unk08;
    int unk0C;
    int unk10;
    int unk14;
    int unk18;
} Instance;

extern Instance *func_00151A00(int);
extern Instance *func_00151A20(int);
extern int func_001533D8(Template *, int, int);
extern int func_0017D088(Template *, int, int);
extern int func_00179818(Template *, int, int, int);
extern int func_001330A8(Template *, int);
extern int func_00100290(Template *, int);
extern int func_0017A498(Template *, int);

Instance *func_00159370(Template *source, unsigned short id) {
    Instance *inst;
    int temporary;

    temporary = 0;
    if ((id >= 0x11C && id < 0x15C) || (id >= 1 && id < 0xFC) ||
        (id >= 0x3A0 && id < 0x458) || id == 0) {
        temporary = 1;
    }
    if (temporary != 0) {
        inst = func_00151A20(0x1C);
    } else {
        inst = func_00151A00(0x1C);
    }
    inst->source = source;
    if (source->unk10 != 0) {
        inst->unk04 = func_001533D8(source, id, 0);
    } else {
        inst->unk04 = 0;
    }
    if (source->unk08 != 0) {
        inst->unk0C = func_0017D088(source, id, 0);
    } else {
        inst->unk0C = 0;
    }
    if (source->unk00 != 0) {
        inst->unk08 = func_00179818(source, id, 0, inst->unk04);
    } else {
        inst->unk08 = 0;
    }
    if (source->unk0C != 0) {
        inst->unk10 = func_001330A8(source, id);
    } else {
        inst->unk10 = 0;
    }
    if (source->unk14 != 0) {
        inst->unk14 = func_00100290(source, id);
    } else {
        inst->unk14 = 0;
    }
    if (source->unk20 != 0) {
        inst->unk18 = func_0017A498(source, id);
    } else {
        inst->unk18 = 0;
    }
    return inst;
}
