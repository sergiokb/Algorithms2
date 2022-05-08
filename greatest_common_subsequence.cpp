#include <iostream>
#include <vector>
int findGCSsize(int& n, int& m, std::vector<int>& v, std::vector<int>& w);
int main() {
    int t, n, m;
    std::vector<int>v;
    std::vector<int>w;
    std::cin >> n;
    v.push_back(0);
    w.push_back(0);
    for(int i = 1; i <= n; i++){
        std::cin >> t;
        v.push_back(t);
    }
    std::cin >> m;
    for(int j = 1; j <= m; j++){
        std::cin >> t;
        w.push_back(t);
    }
    std::cout << findGCSsize(n, m, v, w) << std::endl;
    return 0;
}

int findGCSsize(int& n, int& m, std::vector<int>& v, std::vector<int>& w) {
    std::vector<std::vector<int>>dp(n + 1);
    // dp[i][j] - size of the greatest common subsequence of v and w ending in i and j accordingly
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(i == 0 || j == 0) dp[i].push_back(0);
            else {
                dp[i].push_back(std::max(dp[i][j - 1], dp[i - 1][j]));
                if(v[i] == w[j]) dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    return dp[n][m];
}
