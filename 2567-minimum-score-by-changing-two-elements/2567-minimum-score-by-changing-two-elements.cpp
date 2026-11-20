
class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = nums.size();

        if (n <= 3) return 0;

        int ans = INT_MAX;

        ans = min(ans, nums[n-1] - nums[2]);
        ans = min(ans, nums[n-2] - nums[1]);
        ans = min(ans, nums[n-3] - nums[0]);

        return ans;
    }
};
