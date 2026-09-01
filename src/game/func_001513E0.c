extern int D_002A1E80[];
extern int D_002A3080[];
extern int D_002A4280[];
extern int D_002A5480[];
extern int D_002A6680[];
extern int D_002A7880[];
extern int D_002A8A80[];
extern int D_002A9C80[];

extern int func_00151A00(int arg);
extern int func_00151A20(int arg);
extern void func_00192344(int dst, int src, int arg);
extern void func_00151CA8(int handle);

unsigned int func_001513E0(int kind, int id, int arg) {
    int special;
    int handle;

    special = 0;
    if ((id >= 0x11C && id < 0x15C) || (id >= 1 && id < 0xFC) ||
        (id >= 0x3A0 && id < 0x458) || id == 0) {
        special = 1;
    }
    if (arg == 0 && kind != 0x12) {
        return 0;
    }
    switch (kind) {
    case 8:
        if (D_002A5480[id] == 0) {
            if (special) {
                handle = func_00151A20(arg);
            } else {
                handle = func_00151A00(arg);
            }
            D_002A5480[id] = handle;
        }
        return D_002A5480[id];
    case 9:
        if (D_002A1E80[id] == 0) {
            if (special) {
                handle = func_00151A20(arg);
            } else {
                handle = func_00151A00(arg);
            }
            D_002A1E80[id] = handle;
        }
        return D_002A1E80[id];
    case 11:
        if (D_002A6680[id] == 0) {
            if (special) {
                handle = func_00151A20(arg);
            } else {
                handle = func_00151A00(arg);
            }
            D_002A6680[id] = handle;
        }
        return D_002A6680[id];
    case 12:
        if (D_002A7880[id] == 0) {
            if (special) {
                handle = func_00151A20(arg);
            } else {
                handle = func_00151A00(arg);
            }
            D_002A7880[id] = handle;
        }
        return D_002A7880[id];
    case 14:
        if (D_002A8A80[id] == 0) {
            if (special) {
                handle = func_00151A20(arg);
            } else {
                handle = func_00151A00(arg);
            }
            D_002A8A80[id] = handle;
        }
        return D_002A8A80[id];
    case 15:
        if (D_002A9C80[id] == 0) {
            if (special) {
                handle = func_00151A20(arg);
            } else {
                handle = func_00151A00(arg);
            }
            D_002A9C80[id] = handle;
        }
        return D_002A9C80[id];
    case 4:
        if (D_002A4280[id] == 0) {
            if (special) {
                handle = func_00151A20(arg);
            } else {
                handle = func_00151A00(arg);
            }
            D_002A4280[id] = handle;
        }
        return D_002A4280[id];
    case 16:
        if (D_002A3080[id] == 0) {
            if (special) {
                handle = func_00151A20(arg);
            } else {
                handle = func_00151A00(arg);
            }
            D_002A3080[id] = handle;
        }
        return D_002A3080[id];
    case 17:
        if (special) {
            handle = func_00151A20(arg);
        } else {
            handle = func_00151A00(arg);
        }
        D_002A3080[id] = handle;
        return handle;
    case 20:
        if (special) {
            handle = func_00151A20(arg);
        } else {
            handle = func_00151A00(arg);
        }
        func_00192344(handle, D_002A3080[id], arg);
        func_00151CA8(D_002A3080[id]);
        D_002A3080[id] = handle;
        return handle;
    case 18:
        return D_002A3080[id];
    }
    return 0xFFFFFFFF;
}
