
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;

        for (int i = 0; i < n; i++) {
            map<int, vector<int>> exponents;

            for (int j = i; j < n; j++) {
                int x = nums[j];
                map<int, int> factors;

                for (int p = 2; p * p <= x; p++) {
                    while (x % p == 0) {
                        factors[p]++;
                        x /= p;
                    }
                }

                if (x > 1) factors[x]++;

                // Add zero exponent for previously seen primes.
                for (auto &[p, v] : exponents) {
                    v.push_back(factors[p]);
                }

                // Add newly discovered primes, including earlier zeros.
                for (auto &[p, e] : factors) {
                    if (!exponents.count(p)) {
                        exponents[p] = vector<int>(j - i, 0);
                        exponents[p].push_back(e);
                    }
                }

                bool valid = true;

                for (auto &[p, v] : exponents) {
                    int sum = 0;
                    int mn = INT_MAX;
                    int mx = 0;

                    for (int e : v) {
                        sum += e;
                        mn = min(mn, e);
                        mx = max(mx, e);
                    }

                    if (sum != mn + mx) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};
