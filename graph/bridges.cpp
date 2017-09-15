/*
 * Find bridges.
 *
 * Complexity: O(N + M).
 *
 */


vector<vector<int>> g;
vector<char> used;
vector<int> timer, tin, fup;
 
void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > tin[v])
				// edge (v - to) is bridge
		}
	}
}
 
void find_bridges() {
	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs(i);
}
