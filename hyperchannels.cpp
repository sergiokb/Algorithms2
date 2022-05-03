#include <iostream>
#include <vector>
struct edge {
    int from;
    int to;
    bool used;
};
void euler(int v, std::vector<edge>& e, std::vector<std::vector<int>>& g,
           std::vector<std::vector<int>>& num, std::vector<int>& ptr, std::vector<int>& ans);
int main() {
    std::ios_base::sync_with_stdio(false);
    int n, a;
    std::cin >> n >> a;
    --a;
    std::vector<std::vector<int>>num(n, std::vector<int>(n));
    std::vector<std::vector<int>>g(n);
    std::vector<edge>e(n * n);
    std::vector<int>ans;
    int k = 0;
    int b;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            std::cin >> b;
            if(i == j) continue;
            num[i][j] = k;
            e[num[i][j]].from = i;
            e[num[i][j]].to = j;
            g[i].push_back(num[i][j]);
            if(b == 1) {
                e[num[i][j]].used = true;
            }
            else e[num[i][j]].used = false;
            ++k;
        }
    }
    std::vector<int>ptr(n, 0);
    euler(a, e, g, num, ptr, ans);
    for(int i = ans.size() - 1; i > 0; i--) {
        std::cout << ans[i] + 1 << ' ' << ans[i - 1] + 1 << '\n';
    }
    return 0;
}
void euler(int v, std::vector<edge>& e, std::vector<std::vector<int>>& g,
           std::vector<std::vector<int>>& num, std::vector<int>& ptr, std::vector<int>& ans) {
    while(ptr[v] < g[v].size()) {
        int ee = g[v][ptr[v]];
        if(e[ee].used) {
            ++ptr[v];
            continue;
        }
        int u = e[ee].to;
        e[ee].used = true;
        ++ptr[v];
        euler(u, e, g, num, ptr, ans);
    }
    ans.push_back(v);
}



