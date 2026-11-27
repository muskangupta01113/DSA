class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freeCnt(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    freeCnt[i]++;
                }
            }
        }

        const int NEG = -1000000000;

        vector<int> dp(budget + 1, NEG);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int p = items[i][1];
            int f = freeCnt[i];

            vector<int> ndp = dp;

            for (int r = 0; r < p && r <= budget; r++) {
                int best = NEG;

                for (int t = 1; r + t * p <= budget; t++) {
                    int s = t - 1;
                    int prevCost = r + s * p;

                    if (dp[prevCost] != NEG) {
                        best = max(best, dp[prevCost] - s);
                    }

                    int cost = r + t * p;

                    if (best != NEG) {
                        ndp[cost] = max(ndp[cost], t + f + best);
                    }
                }
            }

            dp = ndp;
        }

        return *max_element(dp.begin(), dp.end());
    }
};