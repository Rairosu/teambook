/*
 * Centroid decomposition.
 *
 * build Complexity: O(N + M).
 *
 */



const int N = 3e4 + 1;

vector<int> g[N];
int sz[N];
bool used[N];
int depth[N];
set<pair<int, int>> in_centroid[N];
vector<pair<int, int>> centroids[N];

void dfs_sz(int v, int prev) {
    sz[v] = 1;
    for (auto to : g[v]) {
        if (used[to] || to == prev)
            continue;
        dfs_sz(to, v);
        sz[v] += sz[to];
    }
}

int find_centroid(int v, int prev, int size) {
    for (auto to : g[v]) {
        if (used[to] || to == prev)
            continue;
        if (sz[to] > size / 2) {
            return find_centroid(to, v, size);
        }
    }
    return v;
}

void relax(int v, int centroid, int prev, int dist) {
    for (auto to : g[v]) {
        if (used[to] || to == prev)
            continue;
        relax(to, centroid, v, dist + 1);
    }
    in_centroid[centroid].insert(make_pair(dist, v));
    centroids[v].push_back(make_pair(dist, centroid));
}

void divide(int v) {
    dfs_sz(v, -1);
    v = find_centroid(v, -1, sz[v]);
    used[v] = true;
    relax(v, v, -1, 0);
    for (auto to : g[v]) {
        if (used[to])
            continue;
        divide(to);
    }
}
