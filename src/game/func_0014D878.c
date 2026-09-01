extern unsigned short D_001ECB0C;

extern void func_00158868(unsigned short id, float *out);

int func_0014D878(unsigned short id) {
    float pos[3];
    int cx;
    int cz;

    func_00158868(id, pos);
    cz = (int)(pos[2] / 98.4251556f);
    cx = (int)(pos[0] / 98.4251404f);
    return cx / 16 + (cz / 16) * D_001ECB0C;
}
