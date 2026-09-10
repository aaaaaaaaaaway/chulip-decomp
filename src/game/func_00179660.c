typedef float Vector[4] __attribute__((aligned(16)));
typedef float Matrix[4][4] __attribute__((aligned(16)));
typedef struct {
    int command0, command1, command2;
    int volume, pan;
    float near_distance, middle_distance, far_distance;
    int near_volume, middle_volume, far_volume;
} Sound;
extern Sound *D_001ED880;
extern Matrix D_001EDC00;
extern void func_001014B0(Vector);
extern void func_0018A3D0(Vector, Matrix, const Vector);
extern void func_0018A608(Vector, const Vector, const Vector);
extern float func_0018A468(const Vector, const Vector);
extern void func_0018A490(Vector, const Vector);
extern float sqrtf(float);
extern void func_0017CA50(int, int, int, int, int, int);
extern void func_0017CAF8(int, int, int, int, int, int, int);

void func_00179660(int flags, int index, const Vector position, int extra) {
    Vector listener, direction;
    Sound *sound = &D_001ED880[index];
    float distance;
    int pan, volume;
    func_001014B0(listener);
    func_0018A3D0(listener, D_001EDC00, listener);
    func_0018A3D0(direction, D_001EDC00, position);
    func_0018A608(direction, direction, listener);
    distance = sqrtf(func_0018A468(direction, direction));
    func_0018A490(direction, direction);
    pan = direction[0] * 63.0f + 64.0f;
    if (distance < sound->near_distance) {
        volume = sound->near_volume;
    } else if (distance < sound->middle_distance) {
        volume = sound->near_volume + (distance - sound->near_distance) *
                                          (sound->middle_volume - sound->near_volume) /
                                          (sound->middle_distance - sound->near_distance);
    } else if (distance < sound->far_distance) {
        volume = sound->middle_volume + (distance - sound->middle_distance) *
                                            (sound->far_volume - sound->middle_volume) /
                                            (sound->far_distance - sound->middle_distance);
    } else {
        volume = sound->far_volume;
    }
    if (volume > 0)
        func_0017CAF8(flags | 0x20000000, sound->command0, sound->command1, sound->command2, volume,
                      pan, extra);
}
