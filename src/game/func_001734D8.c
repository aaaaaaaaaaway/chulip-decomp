int func_0012F5B8();
void func_00173468();

void func_001734D8(unsigned char index, unsigned char enable) {
    int handle;

    handle = func_0012F5B8(index, 3);
    if (enable != 0) {
        func_00173468(handle, 1);
    } else {
        func_00173468(handle, 0);
    }
}
