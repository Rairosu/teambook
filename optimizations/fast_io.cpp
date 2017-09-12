/*
 * Increases speed of reading and writting integers.
 *
 */

void writeInt(int x) {
    char s[10];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n--)
        putc(s[n], stdout);
    putc('\n', stdout);
}

int readInt() {
    int s = 1, x = 0, c = getc(stdin);
    while (c <= 32)
        c = getc(stdin);
    if (c == '-')
        s = -1, c = getc(stdin);
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getc(stdin);
    return x * s;
}
