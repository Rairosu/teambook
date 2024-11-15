/*
 * This file contains realiztaion of Kuhn algorithm.
 * For given bipartite graph 'g' finds maximum matching.
 * 
 * This implementation expects a bipartite graph comprised of disjount sets G1 and G2 with sizes n and k.
 * g[i] contains all possible matches (from G2) for a node i (from G1).
 * 
 * NOTE: This algorithm is faster if n < k.
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
    for (auto to : g[v]) {
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

