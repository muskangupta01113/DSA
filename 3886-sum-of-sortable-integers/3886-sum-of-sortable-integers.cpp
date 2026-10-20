class Solution {
public:
    bool isRotation(vector<int>& a, vector<int>& b,
                    int start, int k) {
        // Build KMP prefix array for block b
        vector<int> lps(k, 0);

        for (int i = 1, len = 0; i < k;) {
            if (b[start + i] == b[start + len]) {
                lps[i++] = ++len;
            } else if (len > 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        // Search b in a+a, without constructing a+a
        int j = 0;

        for (int i = 0; i < 2 * k - 1; i++) {
            int value = a[start + i % k];

            while (j > 0 && value != b[start + j]) {
                j = lps[j - 1];
            }

            if (value == b[start + j]) {
                j++;
            }

            if (j == k) {
                return true;
            }
        }

        return false;
    }

    long long sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        long long ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool valid = true;

            for (int start = 0; start < n; start += k) {
                if (!isRotation(nums, sorted, start, k)) {
                    valid = false;
                    break;
                }
            }

            if (valid) ans += k;
        }

        return ans;
    }
};