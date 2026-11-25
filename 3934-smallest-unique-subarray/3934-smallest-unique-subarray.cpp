
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<int> sa(n), rank(n), temp(n), pos(n), lcp(n);

        vector<int> v = nums;
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = lower_bound(v.begin(), v.end(), nums[i]) - v.begin();
        }

        // Build Suffix Array
        for (int k = 1; k < n; k *= 2) {
            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b])
                    return rank[a] < rank[b];

                int x = (a + k < n) ? rank[a + k] : -1;
                int y = (b + k < n) ? rank[b + k] : -1;

                return x < y;
            });

            temp[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                int x1 = rank[a], x2 = rank[b];
                int y1 = (a + k < n) ? rank[a + k] : -1;
                int y2 = (b + k < n) ? rank[b + k] : -1;

                temp[b] = temp[a] + (x1 != x2 || y1 != y2);
            }

            rank = temp;

            if (rank[sa[n - 1]] == n - 1)
                break;
        }

        // Build inverse suffix array
        for (int i = 0; i < n; i++)
            pos[sa[i]] = i;

        // Calculate LCP
        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            if (r == n - 1) {
                h = 0;
                continue;
            }

            int j = sa[r + 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h])
                h++;

            lcp[r] = h;

            if (h > 0)
                h--;
        }

        // Find minimum unique subarray length
        int ans = n;

        for (int i = 0; i < n; i++) {
            int r = pos[i];
            int mx = 0;

            if (r > 0)
                mx = max(mx, lcp[r - 1]);
            if (r < n - 1)
                mx = max(mx, lcp[r]);

            // Check that a longer prefix exists
            if (mx < n - i)
                ans = min(ans, mx + 1);
        }
        return ans;
    }
};
