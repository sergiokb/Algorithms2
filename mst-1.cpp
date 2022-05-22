#include <iostream>
#include <vector>
#include <map>
int inf = 1e9;
class Heap{
private:
    std::vector<int>a;
    std::vector<int>num;
    std::vector<int>pointer;
    int n = 0;
public:
    void insert(int x, int i){
        if(a.size() <= n + 1) a.resize(2 * n + 2);
        ++n;
        a[n] = x;
        if(pointer.size() <= i) pointer.resize(i + 1);
        if(num.size() <= n) num.resize(2 * n + 1);
        pointer[i] = n;
        num[n] = i;
        siftUp(n);
    }
    int getMinNum(){
        return num[1];
    }
    int getSize() const{
        return n;
    }
    void extractMin(){
        exchange(1, n);
        n--;
        siftDown(1);
    }
    void decreaseKey(int y, int delta){
        a[pointer[y]] -= delta;
        siftUp(pointer[y]);
    }
    void siftUp(int u){
        while(u != 1){
            if(a[u] <= a[u/2]){
                exchange(u, u/2);
                u /= 2;
            }
            else break;
        }
    }
    void siftDown(int u){
        while(2 * u <= n){
            int w = 2 * u;
            if(2 * u + 1 <= n && a[2 * u + 1] < a[2 * u]) w = 2 * u + 1;
            if(a[w] < a[u]){
                exchange(w, u);
                u = w;
            }
            else break;
        }
    }
    void exchange(int p,int q){
        int k = num[p];
        int m = num[q];
        std::swap(num[p], num[q]);
        std::swap(pointer[k], pointer[m]);
        std::swap(a[p], a[q]);
    }
};

int mst(int n, int m, std::vector<std::vector<int>>& g, std::map<std::pair<int, int>, int>& cost);

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>>g(n);
    std::map<std::pair<int, int>, int>cost;
    int fr, to, w;
    for(int i = 0; i < m; i++) {
        std::cin >> fr >> to >> w;
        --fr;
        --to;
        g[fr].push_back(to);
        g[to].push_back(fr);
        cost[{fr, to}] = w;
        cost[{to, fr}] = w;
    }
    std::cout << mst(n, m, g, cost);
    return 0;
}

int mst(int n, int m, std::vector<std::vector<int>>& g, std::map<std::pair<int, int>, int>& cost) {
    std::vector<bool>used(n, false);
    std::vector<int>d(n, inf);
    Heap h;
    for(int i = 0; i < n; i++) {
        h.insert(d[i], i);
    }
    int ans = 0;
    int v = 0;
    int w;
    for(int i = 0; i < n - 1; i++) {
        used[v] = true;
        for(int u: g[v]) {
            if(!used[u] && cost[{u, v}] < d[u]) {
                h.decreaseKey(u, d[u] - cost[{u, v}]);
                d[u] = cost[{u, v}];
            }
        }
        w = h.getMinNum();
        h.extractMin();
        v = w;
        ans += d[v];
    }
    return ans;
}
