
class Solution {
public:
    vector<int> answer;
    vector<vector<int>> adj;
    vector<int> newParent;

    void dfs(int node, vector<int>& parent, string& s,
             vector<int>& last) {

        int ch = s[node] - 'a';
        int old = last[ch];

        if (old != -1) {
            newParent[node] = old;
        } else {
            newParent[node] = parent[node];
        }

        last[ch] = node;

        for (int child : adj[node]) {
            dfs(child, parent, s, last);
        }

        last[ch] = old;
    }

    int calculate(int node) {
        int size = 1;

        for (int child : adj[node]) {
            size += calculate(child);
        }

        answer[node] = size;
        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        adj.assign(n, {});
        answer.assign(n, 0);
        newParent.assign(n, -1);

        
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        
        vector<int> last(26, -1);

        dfs(0, parent, s, last);

      
        adj.assign(n, {});

        for (int i = 1; i < n; i++) {
            adj[newParent[i]].push_back(i);
        }

        
        calculate(0);

        return answer;
    }
};
