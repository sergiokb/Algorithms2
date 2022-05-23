#include <iostream>
#include <vector>
#include <string>
bool cycle_search(int n, std::vector<std::vector<int>>& sons, std::vector<int>& cycle);
void dfs(int v, int p, std::vector<std::string>& color, bool& isCycle,
         std::vector<int>& parent, std::vector<std::vector<int>>& sons, std::vector<int>& cycle);
int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m, a, b;
    std::cin >> n >> m;
    std::vector<std::vector<int>>sons(n);
    for(int i = 0; i < m; i++) {
        std::cin >> a >> b;
        --a;
        --b;
        sons[a].push_back(b);
    }
    std::vector<int>cycle;
    if(cycle_search(n, sons, cycle)) {
        std::cout << "YES" << '\n';
        for(int i = int(cycle.size()) - 1; i >= 0; i--)
            std::cout << cycle[i] + 1 << ' ';
    }
    else std::cout << "NO" << '\n';
    return 0;
}

bool cycle_search(int n, std::vector<std::vector<int>>& sons, std::vector<int>& cycle) {
    bool isCycle = false;
    std::vector<std::string>color(n, "WHITE");
    std::vector<int>parent(n, -1);
    for(int i = 0; i < n; i++) {
        if(color[i] == "WHITE")
            dfs(i, -1, color, isCycle, parent, sons, cycle);
    }
    if(isCycle) return true;
    return false;
}

void dfs(int v, int p, std::vector<std::string>& color, bool& isCycle,
         std::vector<int>& parent, std::vector<std::vector<int>>& sons, std::vector<int>& cycle) {
    parent[v] = p;
    color[v] = "GRAY";
    for(int to: sons[v]) {
        if(color[to] == "WHITE") dfs(to, v, color, isCycle, parent, sons, cycle);
        if(color[to] == "GRAY" && !isCycle) {
            int u = v;
            while(u != to) {
                cycle.push_back(u);
                u = parent[u];
            }
            cycle.push_back(u);
            isCycle = true;
        }
    }
    color[v] = "BLACK";
}
