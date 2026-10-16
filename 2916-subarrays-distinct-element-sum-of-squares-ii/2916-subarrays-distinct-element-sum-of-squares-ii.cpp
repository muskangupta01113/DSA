
class Solution {
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0;
        long long sq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;
    int n;

    void update(int node, int start, int end,
                int l, int r, long long val) {
        if (l > end || r < start)
            return;

        if (l <= start && end <= r) {
            long long len = end - start + 1;
            long long v = val % MOD;

            tree[node].sq =
                (tree[node].sq
                + 2 * v * tree[node].sum % MOD
                + v * v % MOD * len % MOD) % MOD;

            tree[node].sum =
                (tree[node].sum + v * len) % MOD;

            tree[node].lazy =
                (tree[node].lazy + v) % MOD;

            return;
        }

        int mid = start + (end - start) / 2;

        push(node, start, end);

        update(node * 2, start, mid, l, r, val);
        update(node * 2 + 1, mid + 1, end, l, r, val);

        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;

        tree[node].sq =
            (tree[node * 2].sq + tree[node * 2 + 1].sq) % MOD;
    }

    void push(int node, int start, int end) {
        if (tree[node].lazy == 0 || start == end)
            return;

        long long v = tree[node].lazy;
        int mid = start + (end - start) / 2;

        apply(node * 2, start, mid, v);
        apply(node * 2 + 1, mid + 1, end, v);

        tree[node].lazy = 0;
    }

    void apply(int node, int start, int end, long long v) {
        long long len = end - start + 1;

        tree[node].sq =
            (tree[node].sq
            + 2 * v * tree[node].sum % MOD
            + v * v % MOD * len % MOD) % MOD;

        tree[node].sum =
            (tree[node].sum + v * len) % MOD;

        tree[node].lazy =
            (tree[node].lazy + v) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n + 5, Node());

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int right = 0; right < n; right++) {
            int x = nums[right];

            int left = last[x] + 1;

            update(1, 0, n - 1, left, right, 1);

            ans = (ans + tree[1].sq) % MOD;

            last[x] = right;
        }

        return (int)ans;
    }
};
