#define PI 3.1415926f

float func_00152670(int value, int period) {
    int remainder = value % period;

    if (period / 2 < remainder) {
        remainder -= period;
    }
    return remainder * (PI * 2) / (float)period;
}
