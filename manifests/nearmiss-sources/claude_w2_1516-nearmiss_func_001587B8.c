float func_00158698(unsigned short index, unsigned short mode);
void func_00156B00(unsigned short index, unsigned char which, float value);
void func_00156998(unsigned short index, unsigned short id, float value);

float func_001587B8(unsigned short index, unsigned short mode, unsigned short id) {
    float value = func_00158698(index, mode);

    if (id == 0) {
        func_00156B00(index, 1, value);
        return value;
    }
    func_00156998(index, id, value);
    return value;
}
