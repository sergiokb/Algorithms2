#include <iostream>
#include <vector>

class Heap{
private:
    std::vector<int>a;
    std::vector<int>num;
    std::vector<int>pointer;
    int n = 0;
public:
    void insert(int x,int i){
        if(a.size() <= n + 1) a.resize(2 * n + 2);
        ++n;
        a[n] = x;
        pointer.resize(i + 1);
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
    void decreaseKey(int y,int delta){
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

struct edge {
    int to;
    int cost;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m, s, t;
    int inf = 1e9;
    std::cin >> n >> m >> s >> t;
    --s; --t;
    std::vector<std::vector<int>>g(n);
    std::vector<edge>edges(2 * m);
    int fr, to;
    int w;
    for(int i = 0; i < m; i++) {
        std::cin >> fr >> to >> w;
        --fr; --to;
        edges[2 * i].to = to;
        edges[2 * i].cost = w;
        edges[2 * i + 1].to = fr;
        edges[2 * i + 1].cost = w;
        g[fr].push_back(2 * i);
        g[to].push_back(2 * i + 1);
    }
    std::vector<bool>used(n, false);
    std::vector<int>dist(n, inf);
    dist[s] = 0;
    Heap h;
    for(int i = 0; i < n; i++) {
        h.insert(dist[i], i);
    }
    while(true) {
        if(h.getSize() == 0) break;
        int v = h.getMinNum();
        h.extractMin();
        used[v] = true;
        for(int e: g[v]) {
            if(used[edges[e].to]) continue;
            if(dist[edges[e].to] > dist[v] + edges[e].cost) {
                int delta = dist[edges[e].to] - (dist[v] + edges[e].cost);
                dist[edges[e].to] -= delta;
                h.decreaseKey(edges[e].to, delta);
            }
        }
    }
    if(dist[t] == inf) std::cout << -1;
    else std::cout << dist[t];
    return 0;
}


