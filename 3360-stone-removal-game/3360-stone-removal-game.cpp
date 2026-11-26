class Solution {
public:
    bool canAliceWin(int n) {

        int removes = 10;
        bool aliceTurn = true;

        while(n>= removes){

            n = n-removes;
            --removes;
            aliceTurn = !aliceTurn;
        }

        return !aliceTurn;
    }
};