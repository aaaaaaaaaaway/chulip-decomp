extern int func_00138CC8(int, short *, int);
extern void func_00139EB8(int);
extern float func_00154720(unsigned short);
extern int func_00138468(unsigned int, int, unsigned int, unsigned short *);
extern int abs(int);
void func_00156998(unsigned short index, unsigned short duration, float target) {
    short values[4];
    int ticks;
    int event;
    float current, backward, forward, delta;
    if (index == 0xFFFF)
        return;
    ticks = duration ? duration : 1;
    values[0] = index;
    values[2] = ticks;
    event = func_00138CC8(0x1C, (short *)values, 1);
    if (event != -1)
        func_00139EB8(event);
    current = func_00154720(index);
    backward = current - target;
    forward = target - current;
    delta = abs((int)backward) < abs((int)forward) ? backward : forward;
    if (delta > 3.1415927f)
        delta -= 6.2831855f;
    if (delta < -3.1415927f)
        delta += 6.2831855f;
    values[1] = (short)(delta * 1000.0f / (short)values[2]);
    if (values[1] != 0)
        func_00138468(0x1C, 0, 1, (unsigned short *)values);
}
