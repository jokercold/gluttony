#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long 
#define rep(i,a,b) for (int i=a;i<=b;++i)
#define per(i,a,b) for (int i=a;i>=b;--i)
int num,now;
int cost[300000],Next[300000],head[300000];
int v[300000],fa[300000];
int Xor[300000];
int b[4100000][10];
void add(int u,int v1,int z)
{
     ++num;
     cost[num]=z;
     v[num]=v1;
     Next[num]=head[u];
     head[u]=num;
}
void dfs(int u){
     for (int i=head[u];i;i=Next[i])
         if(v[i]!=fa[u]){
             fa[v[i]]=u;
             Xor[v[i]]=Xor[u]^cost[i];
             dfs(v[i]);
         }
}
void build(int u,int x){
     per(i,30,0){
         int t=(x>>i)&1;
         if(!b[u][t])b[u][t]=++now;
         u=b[u][t];
     }  
}
int find(int u,int x){
     int ans=0;
     per(i,30,0){
         int t=(x>>i)&1;
         if(b[u][t^1])u=b[u][t^1],ans+=1<<i;
         else u=b[u][t];
     }  
     return ans;
}
int main(){
    num=0;
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n-1;++i){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    dfs(1);
    now=1;
    rep(i,1,n)
      build(1,Xor[i]);
    int ans=0;
    rep(i,1,n)ans=max(ans,find(1,Xor[i]));
    printf("%d\n",ans);
    //while (1);
    return 0;
}
