typedef struct { float x; float y; float z; float w; } Vec4f;
struct S { unsigned char pad[0x14]; unsigned short f14; short f16; };
extern struct S *D_001ED218;
int func_00154398(unsigned short id);
void func_00158960(unsigned short id, int mode, Vec4f *out);
float func_00105150(Vec4f *v, int angle);
void func_00158868(unsigned short id, Vec4f *out);
void func_00114AB0(int a, Vec4f *src, float c);

void func_0011ED48(void) {
    Vec4f v;
    Vec4f w;
    float d;

    if (func_00154398(D_001ED218->f14) != 0) {
        func_00158960(D_001ED218->f14, 2, &v);
        d = (float)D_001ED218->f16;
        func_00105150(&v, 0x9000);
        d = d - v.y;
        if (d > 0.0f) {
            func_00158868(D_001ED218->f14, &w);
            v.y = w.y;
        }
        v.w = 1.0f;
        v.y = v.y - 12.0f;
        func_00114AB0(1, &v, 0.0f);
    }
}
