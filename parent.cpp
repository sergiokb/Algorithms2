#include <iostream>
#include <vector>
void dfs(int v, int& timer, std::vector<int>& tin, std::vector<int>& tout,
         std::vector<int>& parent, std::vector<std::vector<int>>& sons);
int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m, father, a, b;
    int timer = 0;
    std::cin >> n;
    std::vector<int>parent(n);
    std::vector<std::vector<int>>sons(n);
    for(int i = 0; i < n; i++) {
        std::cin >> parent[i];
        --parent[i];
        if(parent[i] == -1) father = i;
        else sons[parent[i]].push_back(i);
    }
    std::vector<int>tin(n);
    std::vector<int>tout(n);
    dfs(father, timer, tin, tout, parent, sons);
    std::cin >> m;
    for(int i = 0; i < m; i++) {
        std::cin >> a >> b;
        --a;
        --b;
        if(tin[a] < tin[b] && tout[a] > tout[b]) std::cout << 1 << '\n';
        else std::cout << 0 << '\n';
    }
    return 0;
}

void dfs(int v, int& timer, std::vector<int>& tin, std::vector<int>& tout,
         std::vector<int>& parent, std::vector<std::vector<int>>& sons) {
    tin[v] = timer++;
    for(int to: sons[v]) {
        if(to != parent[v]) dfs(to, timer, tin, tout, parent, sons);
    }
    tout[v] = timer++;
}
