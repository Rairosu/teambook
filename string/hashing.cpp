/*
 *
 * Polynomial hashing.
 *
 * Complexity: O(N).
 *
 */


const ll mod = (ll)1e9 + 7;

ll p = rand() % 100 + 100;


ll h[MAXN], deg[MAXN];

void hashing(string s) {

    h[0] = 0, deg[0] = 1;
    for (int i = 0; i < s.size(); i++) {
        h[i + 1] = (h[i] * p) % mod + s[i];
        h[i + 1] %= mod;
        deg[i + 1] = (deg[i] * p) % mod;
    }
    auto get_hash = [&]( int l, int r) { // [l..r]
        return ((h[r + 1] - (h[l] * deg[r - l + 1]) % mod) % mod + mod) % mod;
    };
}
