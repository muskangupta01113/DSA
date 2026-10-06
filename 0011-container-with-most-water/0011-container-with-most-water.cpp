class Solution {
public:
    int maxArea(vector<int>& height) {
        
        int maxarea=0;
        int left=0;
        int right=height.size()-1;

        while(left<right){
           
            int width=right-left;
            int ht=min(height[left],height[right]);
            int currarea = width*ht;

            maxarea=max(maxarea,currarea);

            height[left]<height[right] ? left++ :right--;
        }
        return maxarea;
    }
};