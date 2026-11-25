
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // Coordinate compression
        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        vector<int> s(n + 1);

        for (int i = 0; i < n; i++) {
            s[i] = lower_bound(vals.begin(), vals.end(), nums[i])
                   - vals.begin() + 1;
        }

        s[n] = 0;

        // Build Suffix Array using Counting Sort
        int N = n + 1;

        vector<int> p(N), c(N);
        vector<int> cnt(max(N, (int)vals.size() + 1), 0);

        for (int x : s)
            cnt[x]++;

        for (int i = 1; i < (int)cnt.size(); i++)
            cnt[i] += cnt[i - 1];

        for (int i = N - 1; i >= 0; i--)
            p[--cnt[s[i]]] = i;

        c[p[0]] = 0;
        int classes = 1;

        for (int i = 1; i < N; i++) {
            if (s[p[i]] != s[p[i - 1]])
                classes++;

            c[p[i]] = classes - 1;
        }

        vector<int> pn(N), cn(N);

        for (int h = 0; (1 << h) < N; h++) {
            int shift = 1 << h;

            for (int i = 0; i < N; i++) {
                pn[i] = p[i] - shift;

                if (pn[i] < 0)
                    pn[i] += N;
            }

            fill(cnt.begin(), cnt.begin() + classes, 0);

            for (int x : pn)
                cnt[c[x]]++;

            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];

            for (int i = N - 1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];

            cn[p[0]] = 0;
            int newClasses = 1;

            for (int i = 1; i < N; i++) {
                pair<int, int> cur = {
                    c[p[i]], c[(p[i] + shift) % N]
                };

                pair<int, int> prev = {
                    c[p[i - 1]], c[(p[i - 1] + shift) % N]
                };

                if (cur != prev)
                    newClasses++;

                cn[p[i]] = newClasses - 1;
            }

            c.swap(cn);
            classes = newClasses;

            if (classes == N)
                break;
        }

        // Remove sentinel suffix
        vector<int> sa;

        for (int x : p) {
            if (x != n)
                sa.push_back(x);
        }

        // Build inverse suffix array
        vector<int> pos(n);

        for (int i = 0; i < n; i++)
            pos[sa[i]] = i;

        // Kasai's LCP algorithm
        vector<int> lcp(n, 0);
        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            if (r == 0) {
                h = 0;
                continue;
            }

            int j = sa[r - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[r] = h;

            if (h > 0)
                h--;
        }

        // Find minimum unique subarray length
        int ans = n;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            int longest = lcp[r];

            if (r + 1 < n)
                longest = max(longest, lcp[r + 1]);

            int need = longest + 1;

            // A subarray cannot exceed its suffix length
            if (need <= n - i)
                ans = min(ans, need);
        }

        return ans;
    }
};
