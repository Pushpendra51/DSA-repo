class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int mn = INT_MAX;

        vector<int> freq(n + 1, 0);

        for (auto &x : items) {
            freq[x[0]]++;
            mn = min(mn, x[1]);
        }

        // Count how many different item types each factor divides
        vector<int> cnt(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                cnt[i] += freq[j];
            }
            cnt[i]--; // Exclude the item itself
        }

        // Group bonus purchases by price
        vector<pair<int, long long>> v;

        for (auto &x : items) {
            int factor = x[0];
            int price = x[1];

            if (price <= 2LL * mn && cnt[factor] > 0) {
                v.push_back({price, cnt[factor]});
            }
        }

        sort(v.begin(), v.end());

        long long cost = 0, bonus = 0;

        for (auto &[price, count] : v) {
            long long take = min(count, (budget - cost) / price);

            cost += take * price;
            bonus += take;
        }

        return 2 * bonus + (budget - cost) / mn;
    }
};