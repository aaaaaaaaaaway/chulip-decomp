float func_00113FB0(int value, int period) {
    int rem;

    rem = value % period;
    if (period / 2 < rem) {
        rem = rem - period;
    }
    return (float)rem * 6.2831852f / (float)period;
}
