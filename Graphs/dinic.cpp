#include <bits/stdc++.h>

#define ll long long

using namespace std;

const ll MAXN = 505;
const ll inf = 1e18;

struct edge {
    ll a, b, cap, flow;
};

ll n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<ll> g[MAXN];

void add_edge(ll a, ll b, ll cap) {
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    g[a].push_back(e.size());
    e.push_back(e1);
    g[b].push_back(e.size());
    e.push_back(e2);
}

bool bfs() {
    ll qh = 0, qt = 0;
    q[qt++] = s;
    memset(d, -1, MAXN * sizeof d[0]);
    d[s] = 0;
    while (qh < qt && d[t] == -1) {
        ll v = q[qh++];
        for (size_t i = 0; i < g[v].size(); ++i) {
            ll id = g[v][i],
                    to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

ll dfs(ll v, ll flow) {
    if (!flow) return 0;
    if (v == t) return flow;
    for (; ptr[v] < g[v].size(); ++ptr[v]) {
        ll id = g[v][ptr[v]],
                to = e[id].b;
        if (d[to] != d[v] + 1)  continue;
        ll pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

ll dinic() {
    ll flow = 0;
    for (ll lim = 1 << 30; lim >= 1; ) {
        if (!bfs()) {
            lim >>= 1;
            continue;
        }
        memset(ptr, 0, MAXN * sizeof ptr[0]);
        while (ll pushed = dfs (s, lim))
            flow += pushed;
    }
    return flow;
}

int main() {
#ifdef __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ll m;
    scanf("%lld %lld", &n, &m);
    s = 0, t = n - 1;
    for (ll i = 0; i < m; ++i) {
        ll a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        add_edge(a - 1, b - 1, c);
    }
    printf("%lld", dinic());

    return 0;
}
