class Solution {
public:
    int n, timer;
    vector<vector<int>> adj;
    vector<int> tin, tout, depth;
    vector<vector<int>> up;
    vector<int> bit;
    string s;
    int LOG;

    void dfs(int u, int p) {
        tin[u] = ++timer;

        up[0][u] = p;

        for (int i = 1; i < LOG; i++) {
            up[i][u] = up[i - 1][up[i - 1][u]];
        }

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] ^= val;
        }
    }

    int prefixXor(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res ^= bit[idx];
        }
        return res;
    }

    int pathMask(int u) {
        return prefixXor(tin[u]);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];

        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i)) {
                u = up[i][u];
            }
        }

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }

        return up[0][u];
    }

    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;
        this->s = s;
        timer = 0;

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        adj.assign(n, {});
        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);
        up.assign(LOG, vector<int>(n, 0));
        bit.assign(n + 1, 0);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0, 0);

        // Each node's character contributes to its subtree interval.
        for (int u = 0; u < n; u++) {
            int mask = 1 << (s[u] - 'a');
            add(tin[u], mask);
            add(tout[u] + 1, mask);
        }

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            int u, v;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');

                add(tin[u], oldMask ^ newMask);
                add(tout[u] + 1, oldMask ^ newMask);

                s[u] = c;
            } else {
                ss >> v;

                int w = lca(u, v);

                int mask =
                    pathMask(u) ^
                    pathMask(v) ^
                    (1 << (s[w] - 'a'));

                // A palindrome permutation allows at most one odd count.
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};