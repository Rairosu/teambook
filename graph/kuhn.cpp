/*
 * This file contains realiztaion of Kuhn algorithm.
 * For given bipartite graph 'g' finds maximum matching.
 *
 * Comlexity: O(EV)
 *
 * Requirements: "vector"
 */

int n, k;
vector<vector<int>> g;
vector<int> mt;
vector<char> used;

bool kuhn_step(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || kuhn_step(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

void kuhn() {
    mt.assign(k, -1);
    for (int v = 0; v < n; ++v) {
        used.assign(n, false);
        kuhn_step(v);
    }
}

