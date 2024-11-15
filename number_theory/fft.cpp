/*
 *
 * Fast Fourier Transformation.
 *
 * Complexity: O(NlogN).
 *
 * You can calc fft for 2 polynomials in one run:
 *   fa = A(x) + i*B(x)
 *   fa = fft(fa)
 *
 *   fft(A) = (fa[i] + conj(fa[(n - i) % n])) / base(2, 0)
 *   fft(B) = (fa[i] - conj(fa[(n - i) % n])) / base(0, 2)
 *
 * And you can calc inverse fft:
 *   fb = fft(A) + i*fft(B)
 *   fb = inverse_fft(fb)
 *
 *   A = fb[i].real()
 *   B = fb[i].imag()
 */

const double PI = acos(-1.0);

const int MAXN = 550500;

typedef complex<double> base;

int rev[MAXN];
base fa[MAXN];


void fft(base *a, int lg, bool inv) {
    int n = (1 << lg);
    for(int i = 1; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
        if(rev[i] < i)
            swap(a[i], a[rev[i]]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len;
        if (inv)
            ang *= -1.0;
        base w(1, 0), wn(cos(ang), sin(ang));
        for(int j = 0; j < (len >> 1); j++, w = w * wn)
            for(int i = 0; i < n; i += len) {
                base u = a[i + j], v = w * a[i + j + (len >> 1)];
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
            }
    }
    if (inv) {
        for(int i = 0; i < n; i++)
            a[i] /= n;
    }
}


void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
    int n = 1, lg = 1;
    while (n < max (a.size(), b.size()))
        n <<= 1, ++lg;
    n <<= 1;
    for (int i = 0; i < n; ++i) {
        if (i < a.size() && i < b.size())
            fa[i] = base(a[i], b[i]);
        else if (i < a.size())
            fa[i] = base(a[i], 0);
        else if (i < b.size())
            fa[i] = base(0, b[i]);
        else
            fa[i] = base(0, 0);
    }

    fft (fa, lg, false);
    for (int i = 0; i < n; ++i)
        fa[i] *= fa[i];
    fft (fa, lg, true);

    res.resize(n);
    for (int i = 0; i < n; ++i)
        res[i] = (int)(fa[i].imag() / 2.0 + 0.5);
}

