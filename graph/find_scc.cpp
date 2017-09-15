/*
 *
 * Find strongly connected components.
 *
 * Complexity: O(N + M).
 *
 * Usage:
 *   - g is adjacency table of graph, gr is g reversed
 *
 */



vector<vector<int>> g, gr;
vector<char> used;
vector<int> order, component;
 
void dfs1 (int v) {
	used[v] = true;
	for (int i = 0; i < g[v].size(); ++i)
		if (!used[g[v][i]])
			dfs1(g[v][i]);
	order.push_back (v);
}
 
void dfs2 (int v) {
	used[v] = true;
	component.push_back (v);
	for (int i = 0; i < gr[v].size(); ++i)
		if (!used[gr[v][i]])
			dfs2(gr[v][i]);
}
 
void find_scc() {
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs1(i);
	used.assign (n, false);
	for (int i = 0; i < n; ++i) {
		int v = order[n - 1 - i];
		if (!used[v]) {
			dfs2 (v);
            // print component
			component.clear();
		}
	}
}
