#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define eps 1e-6
#define P(A,B) ((A-1)*m+B)
using namespace std;
int n,m,cnt,S,T;
int d[3000],to[500000],next[500000],head[3000];
int map[60][60],e1[60][60],e2[60][60];
double val[500000],ans,tot;
queue<int> q;
double dfs(int x,double mf)
{
    if(x==T)    return mf;
    int i;
    double temp=mf,k;
    for(i=head[x];i!=-1;i=next[i])
    {
        if(val[i]>eps&&d[to[i]]==d[x]+1)
        {
            k=dfs(to[i],min(temp,val[i]));
            if(k<eps)    d[to[i]]=0;
            val[i]-=k,val[i^1]+=k,temp-=k;
            if(temp<eps) break;
        }
    }
    return mf-temp;
}
int bfs()
{
    while(!q.empty())   q.pop();
    memset(d,0,sizeof(d));
    int i,u;
    q.push(S),d[S]=1;
    while(!q.empty())
    {
        u=q.front(),q.pop();
        for(i=head[u];i!=-1;i=next[i])
        {
            if(!d[to[i]]&&val[i]>eps)
            {
                d[to[i]]=d[u]+1;
                if(to[i]==T)    return 1;
                q.push(to[i]);
            }
        }
    }
    return 0;
}
void add(int a,int b,double c)
{
    to[cnt]=b,val[cnt]=c,next[cnt]=head[a],head[a]=cnt++;
    to[cnt]=a,val[cnt]=0,next[cnt]=head[b],head[b]=cnt++;
}
bool check(double sta)
{
    int i,j;
    memset(head,-1,sizeof(head));
    cnt=0;
    S=0,T=n*m+1;
    ans=0.0;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            add(0,P(i,j),1.0*map[i][j]);
    for(i=1;i<n;i++)
        for(j=1;j<=m;j++)
            add(P(i,j),P(i+1,j),sta*e1[i][j]),add(P(i+1,j),P(i,j),sta*e1[i][j]);
    for(i=1;i<=n;i++)
        for(j=1;j<m;j++)
            add(P(i,j),P(i,j+1),sta*e2[i][j]),add(P(i,j+1),P(i,j),sta*e2[i][j]);
    for(i=1;i<=m;i++)    add(P(1,i),T,sta*e1[0][i]),add(P(n,i),T,sta*e1[n][i]);
    for(i=1;i<=n;i++)    add(P(i,1),T,sta*e2[i][0]),add(P(i,m),T,sta*e2[i][m]);
    while(bfs())    ans+=dfs(0,99999999.999999);
    return tot-ans>eps;
}
int main()
{
    scanf("%d%d",&n,&m);
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%d",&map[i][j]),tot+=1.0*map[i][j];
    for(i=0;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%d",&e1[i][j]);
    for(i=1;i<=n;i++)
        for(j=0;j<=m;j++)
            scanf("%d",&e2[i][j]);
    double l=0.0,r=n*m*100.0,mid;
    while(r-l>eps)
    {
        mid=(l+r)*0.5;
        if(check(mid))  l=mid;
        else    r=mid;
    }
    printf("%.3f",l);
    return 0;
}
