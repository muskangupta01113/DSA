
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        int n = servers.size();
        int m = tasks.size();

        // {weight, index}
        priority_queue<pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>> available;

        // {freeTime, weight, index}
        priority_queue<tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>> busy;

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        long long time = 0;

        for (int j = 0; j < m; j++) {

            time = max(time, (long long)j);

            // Release servers that have completed their tasks
            while (!busy.empty() && get<0>(busy.top()) <= time) {

                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If no server is available, jump to earliest free time
            if (available.empty()) {

                time = get<0>(busy.top());

                while (!busy.empty() && get<0>(busy.top()) <= time) {

                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Assign task to the best available server
            auto [weight, index] = available.top();
            available.pop();

            ans[j] = index;

            // Update server's next available time
            busy.push({time + tasks[j], weight, index});
        }

        return ans;
    }
};
