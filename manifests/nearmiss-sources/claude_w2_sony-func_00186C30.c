typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    unsigned int mant;
} FloatParts;

extern FloatParts D_002DE608[];
extern void func_001866B0(float *value, FloatParts *out);
extern float func_001865A0(FloatParts *p);

float func_00186C30(float x, float y) {
    FloatParts px;
    FloatParts py;
    FloatParts *p;
    float a;
    float b;
    unsigned int q;
    unsigned int bit;
    unsigned int r;
    unsigned int d;

    a = x;
    b = y;
    func_001866B0(&a, &px);
    func_001866B0(&b, &py);
    p = &px;
    if (px.cls < 2) {
        goto done;
    }
    p = &py;
    if (py.cls < 2) {
        goto done;
    }
    px.sign = px.sign ^ py.sign;
    p = &px;
    if ((px.cls ^ 4) != 0) {
        if ((px.cls ^ 2) != 0) {
            if ((py.cls ^ 4) == 0) {
                px.exp = 0;
                px.mant = 0;
                goto done;
            }
            if ((py.cls ^ 2) == 0) {
                px.cls = 4;
                goto done;
            }
            px.exp = px.exp - py.exp;
            r = px.mant;
            d = py.mant;
            if (r < d) {
                px.exp = px.exp - 1;
                r = r << 1;
            }
            q = 0;
            bit = 0x40000000;
            do {
                if (r >= d) {
                    q = q | bit;
                    r = r - d;
                }
                bit = bit >> 1;
                r = r << 1;
            } while (bit != 0);
            if ((q & 0x7F) == 0x40) {
                if ((q & 0x80) == 0) {
                    if (r != 0) {
                        q = q + 0x40;
                    }
                } else {
                    q = q + 0x40;
                }
            }
            px.mant = q;
            goto done;
        }
    }
    if (px.cls == py.cls) {
        p = D_002DE608;
    }
done:
    return func_001865A0(p);
}
