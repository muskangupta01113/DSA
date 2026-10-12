class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        
        int totgas=0;
        int totcost=0;

        for(int i=0;i<gas.size();i++){
            totgas += gas[i];
        }
        for(int j=0;j<cost.size();j++){
            totcost += cost[j];
        }
        if(totgas < totcost){
            return -1;
        }

        int start=0;
        int currgas =0;

        for(int k=0;k<gas.size();k++){
            currgas += gas[k]-cost[k];
            if(currgas<0){
                start=k+1;
                currgas =0;
            }
        }
        return start;
    }
};