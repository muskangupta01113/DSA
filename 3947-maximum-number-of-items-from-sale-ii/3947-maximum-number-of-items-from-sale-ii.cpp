
class Solution {
public:
    long long maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

       
        long long p = LLONG_MAX;
        vector<int> freq(n + 1, 0);

        for (auto &it : items) {
            freq[it[0]]++;
            p = min(p, (long long)it[1]);
        }

        
        vector<int> cnt(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                cnt[i] += freq[j];
            }
        }

       
        vector<pair<long long, int>> v;

        for (auto &it : items) {
            int factor = it[0];
            long long price = it[1];

            int d = cnt[factor] - 1;

            if (price < 2 * p && d > 0) {
                v.push_back({price - p, d});
            }
        }

        
        sort(v.begin(), v.end());

        long long spent = 0;
        long long bought = 0;

        for (auto &it : v) {
            long long extra = it.first;
            long long limit = it.second;

            long long cost = p + extra;

            long long canBuy = (budget - spent) / cost;

            long long take = min(limit, canBuy);

            bought += take;
            spent += take * cost;
        }

        
        long long ans = 2 * bought + (budget - spent) / p;

        return ans;
    }
};
