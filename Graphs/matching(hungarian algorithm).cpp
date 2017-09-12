#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int inf = 1e9;
const int MAXN = 2e6 + 10;

char buffer[MAXN];

vector<vector<int>> g;

int cost = 0;
vector<int> matching(int n) {
    vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(n + 1, inf);
        vector<char> used(n + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], delta = inf, j1;
            for (int j = 1; j <= n; ++j)
                if (!used[j]) {
                    int cur = g[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= n; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> res(n + 1);
    for (int j = 1; j <= n; ++j)
        res[p[j]] = j;
    cost = -v[0];
    return res;
}


int main() {
#ifdef __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, k;
    scanf("%d %d", &n, &k);
    g.resize(k + 1, vector<int>(k + 1));
    string a, b;
    scanf("%s", buffer);
    a = string(buffer);
    scanf("%s", buffer);
    b = string(buffer);
    for (int i = 0; i < n; ++i) {
        int x = a[i] >= 'a'? (a[i] - 'a') : (26 + a[i] - 'A');
        int y = b[i] >= 'a'? (b[i] - 'a') : (26 + b[i] - 'A');
        g[x + 1][y + 1] -= 1;
    }
    vector<int> res = matching(k);
    printf("%d\n", abs(cost));
    for (int i = 1; i <= k; ++i) {
        char cur = res[i] > 26? ('A' + res[i] - 26) : ('a' + res[i]);
        printf("%c", cur - 1);
    }

    return 0;
}
