class Solution {
public:
    int minMoves2(vector<int>& nums) {

        sort(nums.begin(),nums.end());

        int n= nums.size();
        int mid = nums[n/2];
        int moves =0;

        for(int i=0;i<n/2;i++){
            moves += abs(nums[i]-mid);
            moves += abs(nums[n-i-1]-mid);
        }
        return moves;
        
    }
};