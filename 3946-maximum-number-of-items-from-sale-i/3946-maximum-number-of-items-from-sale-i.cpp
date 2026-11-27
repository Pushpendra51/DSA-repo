
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int minPrice = 1501;

        for (auto &x : items)
            minPrice = min(minPrice, x[1]);

        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; i++) {
            int freeItems = 0;

            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0)
                    freeItems++;
            }

            int cost = items[i][1];
            int benefit = 1 + freeItems;

            for (int b = budget; b >= cost; b--) {
                dp[b] = max(dp[b], dp[b - cost] + benefit);
            }
        }

        int ans = 0;

        for (int b = 0; b <= budget; b++) {
            ans = max(ans, dp[b] + (budget - b) / minPrice);
        }

        return ans;
    }
};
