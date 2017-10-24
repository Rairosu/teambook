/*
 *
 * Find min cost max flow
 *
 * Complexity: ~ O(MN^3).
 */


const int N = (int)250;

struct Edge {
    int to;
    int cap;
    int cost;
    int flow;
    int id;
    int rid;
    int from;
    Edge() = default;
    Edge(int to, int cap, int cost, int flow, int id, int rid, int from) :
                to(to), cap(cap),
                cost(cost), flow(flow),
                id(id), rid(rid), from(from) {}
};

int s = N - 4, t = N - 3;

vector<int> g[N];

vector<Edge> e;

void add_edge(int u, int v, int cap, int cost) {
    g[u].push_back(e.size());
    e.push_back(Edge(v, cap, cost, 0, e.size(), g[v].size(), u));
    g[v].push_back(e.size());
    e.push_back(Edge(u, 0, -cost, 0, e.size(), g[u].size() - 1, v));
}

pair<int, int> find_flow() {
    int flow = 0;
    int cost = 0;
    while (flow < sum) {
        vector<int> id(N, 0);
        vector<int> d(N, inf);
        vector<int> q(N);
        vector<int> p(N);
        vector<size_t> p_edge(N);
        int qh = 0, qt = 0;
        q[qt++] = s;
        d[s] = 0;
        while (qh != qt) {
            int v = q[qh++];
            id[v] = 2;
            if (qh == N) qh = 0;
            for (size_t i = 0; i < g[v].size(); ++i) {
                Edge& r = e[g[v][i]];
                if (r.flow < r.cap && d[v] + r.cost < d[r.to]) {
                    d[r.to] = d[v] + r.cost;
                    if (id[r.to] == 0) {
                        q[qt++] = r.to;
                        if (qt == N) qt = 0;
                    } else if (id[r.to] == 2) {
                        if (--qh == -1) qh = N - 1;
                        q[qh] = r.to;
                    }
                    id[r.to] = 1;
                    p[r.to] = v;
                    p_edge[r.to] = i;
                }
            }
        }
        if (d[t] == inf)  break;
        int addflow = sum - flow;
        for (int v = t; v != s; v = p[v]) {
            int pv = p[v];
            size_t pr = p_edge[v];
            addflow = min(addflow, e[g[pv][pr]].cap - e[g[pv][pr]].flow);
        }
        int add_cost = 0;
        for (int v = t; v != s; v = p[v]) {
            int pv = p[v];
            size_t pr = p_edge[v];
            size_t r = e[g[pv][pr]].rid;
            e[g[pv][pr]].flow += addflow;
            e[g[v][r]].flow -= addflow;
            add_cost += e[g[pv][pr]].cost * addflow;
        }
        flow += addflow;
        cost += add_cost;
    }
    return {flow, cost};
}

