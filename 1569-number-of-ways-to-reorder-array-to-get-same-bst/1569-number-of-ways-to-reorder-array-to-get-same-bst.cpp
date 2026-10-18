
class Solution {
public:
    long long MOD = 1e9 + 7;
    long long comb[1001][1001];

    long long solve(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2)
            return 1;

        vector<int> left, right;

        // First element becomes the root
        int root = nums[0];

        // Divide elements into left and right subtrees
        for (int i = 1; i < n; i++) {
            if (nums[i] < root)
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        long long leftWays = solve(left);
        long long rightWays = solve(right);

        // Interleave left and right elements
        long long ways = comb[n - 1][left.size()];

        ways = ways * leftWays % MOD;
        ways = ways * rightWays % MOD;

        return ways;
    }

    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        // Precompute combinations using Pascal's triangle
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i)
                    comb[i][j] = 1;
                else
                    comb[i][j] =
                        (comb[i - 1][j - 1] +
                         comb[i - 1][j]) % MOD;
            }
        }

        // Subtract the original ordering
        return (solve(nums) - 1 + MOD) % MOD;
    }
};
