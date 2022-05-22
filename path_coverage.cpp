#include <iostream>
#include <vector>
int path_coverage(int n, int m, std::vector<std::vector<int>>& g);
bool augment(int v, std::vector<std::vector<int>>& g, std::vector<bool>& used, std::vector<int>& match);
bool dfs(int v, std::vector<int>& match, std::vector<bool>& used);

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>>g(n);
    int fr, to;
    for(int i = 0; i < m; ++i) {
        std::cin >> fr >> to;
        --fr;
        --to;
        g[fr].push_back(to);
    }
    std::cout << path_coverage(n, m, g);
    return 0;
}

int path_coverage(int n, int m, std::vector<std::vector<int>>& g) {
    std::vector<bool>used(n, false);
    std::vector<int>match(n, -1);
    for(int v = 0; v < n; ++v) {
        if(augment(v, g, used, match)) {
            used.assign(n, false);
        }
    }
    used.assign(n, false);
    int ans = 0;
    for(int v = 0; v < n; ++v) {
        if(used[v]) continue;
        if(dfs(v, match, used)) ++ans;
    }
    return ans;
}

bool augment(int v, std::vector<std::vector<int>>& g, std::vector<bool>& used, std::vector<int>& match) {
    if(used[v]) return false;
    used[v] = true;
    for(int to: g[v]) {
        if(match[to] == -1 || augment(match[to], g, used, match)) {
            match[to] = v;
            return true;
        }
    }
    return false;
}

bool dfs(int v, std::vector<int>& match, std::vector<bool>& used) {
    used[v] = true;
    int to = match[v];
    if(to == -1) return true;
    if(used[to]) return false;
    return dfs(to, match, used);
}



