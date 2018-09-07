#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
vector <int> g[maxn], low, high;
map <int, int> mp[maxn];
int n, m, in[maxn], vis[maxn];
 
int main()
{
    scanf("%d %d", &n,&m);
    for(int i=1; i<=m; i++){
        int x,y;
        scanf("%d %d", &x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
        mp[x][y] = 1;
        mp[y][x] = 1;
        in[x]++;
        in[y]++;
    }
    for(int i=1; i<=n; i++){
        if(in[i]<=sqrt(m)) low.push_back(i);
        else high.push_back(i);
    }
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i=0; i<low.size(); i++){
        int x = low[i];
        vis[x] = 1;
        for(int j=0; j<g[x].size(); j++){
            int y = g[x][j];
            if(vis[y]) continue;
            for(int k=j+1; k<g[x].size(); k++){
                int z = g[x][k];
                if(vis[z]) continue;
                if(mp[y].count(z)) ans++;
            }
        }
    }
    for(int i=0; i<high.size(); i++){
        for(int j=i+1; j<high.size(); j++){
            int x, y, z;
            x = high[i];
            y = high[j];
            if(mp[x].count(y)==0) continue;
            for(int k=j+1; k<high.size(); k++){
                z = high[k];
                if(mp[y].count(z)&&mp[x].count(z)) ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
