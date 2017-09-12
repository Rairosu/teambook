/*
 * Increases speed of memory allocating and deleting.
 * Memory doesn't reallocates. May cause MLE or RE.
 */

const int SZ = 5e7;
char buf[SZ];
int pos;

void * operator new(size_t x) {
    pos += x;
    if (pos > SZ) {
        throw 42;
    }
    return buf + pos - x;
}

void operator delete(void *x) {}
