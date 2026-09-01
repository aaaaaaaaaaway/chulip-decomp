typedef struct {
    unsigned short unk00;
    unsigned short unk02;
    unsigned char pad04[4];
    unsigned short unk08;
    unsigned short unk0A;
    unsigned char pad0C[0x14];
} SoundTrack;

typedef struct {
    unsigned char pad00[0x20];
    unsigned short unk20;
    unsigned char pad22[6];
    int unk28;
    unsigned char pad2C[4];
    unsigned short unk30;
} SoundVoice;

struct VoiceRef {
    SoundVoice *voice;
    int pad;
};

extern SoundTrack *D_001ECF70;
extern struct VoiceRef D_001ED940;

extern SoundVoice *func_0017D040(int);
extern void func_00151CA8(int);
extern void func_0017E630(int);
extern void func_0017E9B0(int);

void func_0017EFE0(void) {
    int i;

    for (i = 0; i < 0x38; i++) {
        if (D_001ECF70[i].unk08 != 0) {
            D_001ED940.voice = func_0017D040(D_001ECF70[i].unk00);
            if (D_001ED940.voice->unk30 == 0xFFFF) {
                if (D_001ED940.voice->unk28 != 0) {
                    func_00151CA8(D_001ED940.voice->unk28);
                }
                D_001ED940.voice->unk28 = 0;
                func_0017E630(D_001ECF70[i].unk08);
                D_001ECF70[i].unk08 = 0;
                D_001ED940.voice->unk20 = 0;
            } else {
                func_0017E9B0(D_001ECF70[i].unk08);
                D_001ECF70[i].unk08 = 0;
                D_001ED940.voice->unk20 = 0;
            }
        }
        if (D_001ECF70[i].unk0A != 0) {
            D_001ED940.voice = func_0017D040(D_001ECF70[i].unk02);
            if (D_001ED940.voice->unk30 == 0xFFFF) {
                if (D_001ED940.voice->unk28 != 0) {
                    func_00151CA8(D_001ED940.voice->unk28);
                }
                D_001ED940.voice->unk28 = 0;
                func_0017E630(D_001ECF70[i].unk0A);
                D_001ECF70[i].unk0A = 0;
                D_001ED940.voice->unk20 = 0;
            } else {
                func_0017E9B0(D_001ECF70[i].unk0A);
                D_001ECF70[i].unk0A = 0;
                D_001ED940.voice->unk20 = 0;
            }
        }
    }
}
