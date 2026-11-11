
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long both = min(need1, need2);

      
        long long option1 = both * costBoth +
                            1LL * (need1 - both) * cost1 +
                            1LL * (need2 - both) * cost2;

        long long option2 = 1LL * need1 * cost1 +
                            1LL * need2 * cost2;

        
        long long option3 = 1LL * max(need1, need2) * costBoth;

        return min({option1, option2, option3});
    }
};
