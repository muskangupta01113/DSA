
class Solution {
    vector<long long> pref, sum;
    vector<int> mx, lazy;
    vector<bool> hasLazy;
    int n;

    void apply(int p, int l, int r, int v) {
        mx[p] = v;
        sum[p] = 1LL * v * (r - l + 1)
               - (pref[r + 1] - pref[l]);
        lazy[p] = v;
        hasLazy[p] = true;
    }

    void push(int p, int l, int r) {
        if (!hasLazy[p] || l == r) return;
        int m = (l + r) / 2;
        apply(p * 2, l, m, lazy[p]);
        apply(p * 2 + 1, m + 1, r, lazy[p]);
        hasLazy[p] = false;
    }

    void update(int p, int l, int r,
                int ql, int qr, int v) {
        if (ql > r || qr < l) return;

        if (ql <= l && r <= qr) {
            apply(p, l, r, v);
            return;
        }

        push(p, l, r);
        int m = (l + r) / 2;

        update(p * 2, l, m, ql, qr, v);
        update(p * 2 + 1, m + 1, r, ql, qr, v);

        mx[p] = max(mx[p * 2], mx[p * 2 + 1]);
        sum[p] = sum[p * 2] + sum[p * 2 + 1];
    }

    long long querySum(int p, int l, int r,
                       int ql, int qr) {
        if (ql > r || qr < l) return 0;

        if (ql <= l && r <= qr) return sum[p];

        push(p, l, r);
        int m = (l + r) / 2;

        return querySum(p * 2, l, m, ql, qr)
             + querySum(p * 2 + 1, m + 1, r, ql, qr);
    }

    int findFirst(int p, int l, int r,
                  int ql, int qr, int v) {
        if (r < ql || l > qr || mx[p] < v)
            return qr + 1;

        if (l == r) return l;

        push(p, l, r);
        int m = (l + r) / 2;

        int x = findFirst(p * 2, l, m, ql, qr, v);
        if (x <= qr) return x;

        return findFirst(p * 2 + 1, m + 1, r, ql, qr, v);
    }

public:
    long long countNonDecreasingSubarrays(
        vector<int>& nums, int k) {

        n = nums.size();

        pref.assign(n + 1, 0);
        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + nums[i];

        sum.assign(4 * n + 5, 0);
        mx.assign(4 * n + 5, INT_MIN);
        lazy.assign(4 * n + 5, 0);
        hasLazy.assign(4 * n + 5, false);

        int r = n - 1;
        long long cost = 0, ans = 0;

        for (int l = n - 1; l >= 0; l--) {

            update(1, 0, n - 1, l, l, nums[l]);

            if (l < r) {
                int p = findFirst(
                    1, 0, n - 1,
                    l + 1, r, nums[l]
                );

                if (p > l + 1) {
                    long long oldCost = querySum(
                        1, 0, n - 1, l + 1, p - 1
                    );

                    update(
                        1, 0, n - 1,
                        l + 1, p - 1, nums[l]
                    );

                    long long newCost = querySum(
                        1, 0, n - 1, l + 1, p - 1
                    );

                    cost += newCost - oldCost;
                }
            }

            while (cost > k && l <= r) {
                cost -= querySum(1, 0, n - 1, r, r);
                r--;
            }

            ans += r - l + 1;
        }

        return ans;
    }
};
