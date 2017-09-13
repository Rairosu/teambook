/*
 * This file contains realization of Dinic algorithm.
 * For given graph 'g' finds maximal flow in O(EV^2).
 *
 * MAXN - maximal number of vertex in G
 * s - start vertex
 * t - end vertex
 *
 * dinic() - runs algorithm, returns max flow
 * add_edge(a, b, cap) - add edge from 'a' to 'b' with capacity 'cap'
 *
 * Requirements: "vector", "cstring"
 */

const long long MAXN = 505;
const long long inf = 1e18;

struct edge {
    long long a, b, cap, flow;
};

long long n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<long long> g[MAXN];

void add_edge(long long a, long long b, long long cap) {
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    g[a].push_back(e.size());
    e.push_back(e1);
    g[b].push_back(e.size());
    e.push_back(e2);
}

bool bfs() {
    long long qh = 0, qt = 0;
    q[qt++] = s;
    memset(d, -1, MAXN * sizeof d[0]);
    d[s] = 0;
    while (qh < qt && d[t] == -1) {
        long long v = q[qh++];
        for (size_t i = 0; i < g[v].size(); ++i) {
            long long id = g[v][i],
                    to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

long long dfs(long long v, long long flow) {
    if (!flow) return 0;
    if (v == t) return flow;
    for (; ptr[v] < g[v].size(); ++ptr[v]) {
        long long id = g[v][ptr[v]],
                to = e[id].b;
        if (d[to] != d[v] + 1)  continue;
        long long pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

long long dinic() {
    long long flow = 0;
    for (long long lim = 1 << 30; lim >= 1; ) {
        if (!bfs()) {
            lim >>= 1;
            continue;
        }
        memset(ptr, 0, MAXN * sizeof ptr[0]);
        while (long long pushed = dfs (s, lim))
            flow += pushed;
    }
    return flow;
}

