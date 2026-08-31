unsigned char func_00128AC0(const short *values)
{
    int best_index = -1;
    int best_value = -0x7FFF;
    int index = 0;

    do {
        int value = *values;

        if (best_value < value) {
            best_value = value;
            best_index = index;
        }
        index++;
        values++;
    } while (index < 4);

    return best_index;
}
