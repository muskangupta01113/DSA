
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        unordered_map<int, int> dp;
        int ans = 0;

        for (int x : nums) {
            int takeOriginal = dp[x - 1] + 1;
            int takeIncreased = dp[x] + 1;

            dp[x + 1] = max(dp[x + 1], takeIncreased);
            dp[x] = max(dp[x], takeOriginal);

            ans = max({ans, dp[x], dp[x + 1]});
        }

        return ans;
    }
};
