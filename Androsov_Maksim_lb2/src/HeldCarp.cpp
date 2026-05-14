#include <bits/stdc++.h>


using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    int N = 1 << n;
    vector<vector<int>> dp(N, vector<int>(n, INF));
    vector<vector<int>> parent(N, vector<int>(n, -1));

    dp[1][0] = 0;

    for (int mask = 1; mask < N; mask++) {
        for (int curr = 0; curr < n; curr++) {
            if (!(mask & (1 << curr))) continue;
            if (dp[mask][curr] == INF) continue;

            for (int next = 0; next < n; next++) {
                if (mask & (1 << next)) continue;


                if (matrix[curr][next] == 0) continue;

                int newMask = mask | (1 << next);

                int newCost = dp[mask][curr] + matrix[curr][next];

                if (newCost < dp[newMask][next]) {
                    dp[newMask][next] = newCost;
                    parent[newMask][next] = curr;
                }
            }
        }
    }

    int fullMask = N - 1;
    int ans = INF;
    int last = -1;

    for (int i = 1; i < n; i++) {
        if (dp[fullMask][i] == INF || matrix[i][0] == 0) continue;

        int total = dp[fullMask][i] + matrix[i][0];
        if (total < ans) {
            ans = total;
            last = i;
        }
    }

    if (ans == INF) {
        cout << "no path\n";
        return 0;
    }

    cout << ans << "\n";


    vector<int> path;
    int cur = last;
    int mask = fullMask;

    while (cur != -1) {
        path.push_back(cur);
        int prev = parent[mask][cur];
        mask ^= (1 << cur);
        cur = prev;
    }

    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << 0 << "\n";

    return 0;
}
