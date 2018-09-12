#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
bool flag[1000005];
int dis[1000005];
struct node{
       int v,len;
};
bool operator <(node a,node b){
     return a.len>b.len;
}
bool operator >(node a,node b){
     return a.len<b.len;
}
priority_queue <node> heap;
vector<node> vec[1000005];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    while (m--){
          int u,v,len;
          scanf("%d%d%d",&u,&v,&len);
          vec[u].push_back((node){v,len});
          vec[v].push_back((node){u,len});
    }
    for (int i=1;i<=n;++i)
        dis[i]=1<<29,flag[i]=false;
    dis[1]=0;
    heap.push((node){1,0});
    while (!heap.empty()){
          node n1=heap.top();
          heap.pop();
          if (!flag[n1.v]){
             int u=n1.v;
             flag[u]=true;
             for (int i=vec[u].size()-1;i>=0;--i)
             {
                 int v=vec[u][i].v,len=vec[u][i].len;
                 if (!flag[v] && dis[u]+len<dis[v]){
                    dis[v]=dis[u]+len;
                    heap.push((node){v,dis[v]});
                 }
             }
          }
    }
    printf("%d\n",dis[n]);
    //while (1);
    return 0;
}
