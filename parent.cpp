#include <iostream>
#include <vector>
void solution(int n, int m, std::vector<int>& ans,
              std::vector<int>& input, std::vector<std::pair<int, int>>& pairs);
void dfs(int v, int& timer, std::vector<int>& tin, std::vector<int>& tout,
         std::vector<int>& parent, std::vector<std::vector<int>>& sons);
int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n;
    std::vector<int>input(n);
    for(int i = 0; i < n; i++) {
        std::cin >> input[i];
    }
    std::cin >> m;
    std::vector<std::pair<int, int>>pairs(m);
    for(int i = 0; i < m; i++) {
        std::cin >> pairs[i].first >> pairs[i].second;
    }
    std::vector<int>ans(m);
    solution(n, m, ans, input, pairs);
    for(int i = 0; i < m; i++) {
        std::cout << ans[i] << '\n';
    }
    return 0;
}

void solution(int n, int m, std::vector<int>& ans,
              std::vector<int>& input, std::vector<std::pair<int, int>>& pairs) {
    int father, a, b;
    std::vector<int>parent(n);
    std::vector<std::vector<int>>sons(n);
    for(int i = 0; i < n; i++) {
        parent[i] = input[i];
        --parent[i];
        if(parent[i] == -1) father = i;
        else sons[parent[i]].push_back(i);
    }
    int timer = 0;
    std::vector<int>tin(n);
    std::vector<int>tout(n);
    dfs(father, timer, tin, tout, parent, sons);
    for(int i = 0; i < m; i++) {
        a = pairs[i].first - 1;
        b = pairs[i].second - 1;
        if(tin[a] < tin[b] && tout[a] > tout[b]) ans[i] = 1;
        else ans[i] = 0;
    }
}

void dfs(int v, int& timer, std::vector<int>& tin, std::vector<int>& tout,
         std::vector<int>& parent, std::vector<std::vector<int>>& sons) {
    tin[v] = timer++;
    for(int to: sons[v]) {
        if(to != parent[v]) dfs(to, timer, tin, tout, parent, sons);
    }
    tout[v] = timer++;
}
