char *func_00192D50(const char *searchee, const char *lookfor) {
    const char *s;
    int i;

    if (*searchee == 0) {
        if (*lookfor != 0) {
            return 0;
        }
        return (char *)searchee;
    }
    while (*searchee != 0) {
        s = searchee;
        i = 0;
        for (;;) {
            if (lookfor[i] == 0) {
                return (char *)searchee;
            }
            if (lookfor[i] != s[i]) {
                break;
            }
            i++;
        }
        searchee++;
    }
    return 0;
}
