int func_0017D7E0(int kind, int variant) {
    switch (kind) {
    case 0:
    case 1:
    case 2:
    case 10:
        return 0;
    case 19:
    case 27:
        return variant ? 2 : 4;
    case 20:
    case 36:
    case 44:
        return 1;
    }
    return 0;
}
