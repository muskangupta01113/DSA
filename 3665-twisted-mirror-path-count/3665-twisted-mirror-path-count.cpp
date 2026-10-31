
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        const int MOD = 1e9 + 7;

        vector<vector<long long>> fromLeft(m, vector<long long>(n, 0));
        vector<vector<long long>> fromTop(m, vector<long long>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                long long left = fromLeft[i][j];
                long long top = fromTop[i][j];

                // Starting position
                if (i == 0 && j == 0) {
                    left = 1;
                }

                // Destination
                if (i == m - 1 && j == n - 1) {
                    if (grid[i][j] == 1)
                        return 0;

                    return (left + top) % MOD;
                }

                if (grid[i][j] == 1) {
                    // Mirror: Right -> Down
                    if (i + 1 < m) {
                        fromTop[i + 1][j] =
                            (fromTop[i + 1][j] + left) % MOD;
                    }

                    // Mirror: Down -> Right
                    if (j + 1 < n) {
                        fromLeft[i][j + 1] =
                            (fromLeft[i][j + 1] + top) % MOD;
                    }
                }
                else {
                    long long ways = (left + top) % MOD;

                    // Move right
                    if (j + 1 < n) {
                        fromLeft[i][j + 1] =
                            (fromLeft[i][j + 1] + ways) % MOD;
                    }

                    // Move down
                    if (i + 1 < m) {
                        fromTop[i + 1][j] =
                            (fromTop[i + 1][j] + ways) % MOD;
                    }
                }
            }
        }

        return 0;
    }
};
