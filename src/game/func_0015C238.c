typedef struct Animation {
    unsigned char unknown00[0x14];
    unsigned int limit, flags, sequence;
    unsigned int unknown20;
    float frame, speed, alternate_speed;
} Animation;
typedef struct Owner {
    unsigned char unknown00[0x14];
    Animation *animation;
} Owner;
typedef struct Actor {
    unsigned char unknown00[0x24];
    Owner *owner;
    unsigned char unknown28[0xE];
    unsigned short kind;
    unsigned char unknown38[8];
} Actor;
typedef struct Snapshot {
    unsigned int default_sequence, flags, limit, sequence;
    float unknown10, frame, speed, alternate_speed;
} Snapshot;
typedef struct FrameRange {
    unsigned short start, end;
} FrameRange;
typedef struct FrameBank {
    unsigned int length;
    FrameRange ranges[127];
} FrameBank;
typedef struct Control {
    long flags;
} Control;
extern Actor D_002ABA40[];
extern Snapshot D_002CFA40[];
extern FrameBank D_001A8C00[];
extern Control *func_00136AE8(void);
extern int func_00154560(unsigned short);
extern void func_0015D410(int, int);
int func_0015C238(unsigned short index) {
    int result = 0;
    unsigned short kind;
    Animation *state;
    FrameBank *bank;
    Snapshot *snapshot;
    if (index >= 0x1C0)
        return 0;
    kind = (D_002ABA40 + index)->kind;
    if (kind == 0xFFFF || (D_002ABA40 + index)->owner == 0)
        return 0;
    state = (D_002ABA40 + index)->owner->animation;
    if (state == 0)
        return 0;
    bank = D_001A8C00 + kind;
    snapshot = D_002CFA40 + index;
    if (state->flags & 2) {
        if ((state->flags & 0x2200) != 0x200 && !(state->flags & 4)) {
            if (state->flags & 0x80)
                state->frame += state->alternate_speed;
            else
                state->frame += state->speed;
        }
        result = 1;
        if (state->frame >= state->limit) {
            state->frame = state->limit;
            if (state->flags & 0x81) {
                unsigned int sequence = state->sequence;
                if (state->flags & 0x10) {
                    state->frame = bank->length - bank->ranges[sequence].end + 1;
                    state->limit = bank->length - bank->ranges[sequence].start + 1;
                } else {
                    state->frame = bank->ranges[sequence].start;
                    state->limit = bank->ranges[sequence].end;
                }
                if (state->flags & 0x80)
                    state->flags &= ~0x180U;
                snapshot->frame = state->frame;
                snapshot->limit = state->limit;
                if (func_00154560(index))
                    func_0015D410(index, state->sequence);
            } else {
                state->flags &= ~0x2002U;
                snapshot->default_sequence = state->sequence;
                state->sequence = 0;
                snapshot->flags = state->flags;
                snapshot->sequence = state->sequence;
            }
        }
        if (state->flags & 0x40) {
            state->flags |= 4;
            state->flags &= ~0x40U;
        }
    }
    return result;
}
