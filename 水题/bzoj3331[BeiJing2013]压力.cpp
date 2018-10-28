#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 400100
int Num,num,idx,T,cnt;
int dfn[N],low[N],st[N],Hed[N],hed[N];
struct node{
	int v,Next;
};
node e[N];
node E[N];
int dep[N],tot[N],f[N][30],Q[N];
void Add(int u,int v){
	++Num;
	E[Num].v=v;
	E[Num].Next=Hed[u];
	Hed[u]=Num;
}
void add(int u,int v){
	++num;
	e[num].v=v;
	e[num].Next=hed[u];
	hed[u]=num;
}
void tarjan(int x){
	dfn[x]=low[x]=++idx;
	st[++T]=x;
	for (int i=Hed[x];i!=-1;i=E[i].Next){
		int v=E[i].v;
		if (!dfn[v]){
			tarjan(v);
			low[x]=min(low[x],low[v]);
			if (low[v]>=dfn[x]){
				cnt++;int j;
				do{
					j=st[T--];
					add(j,cnt);add(cnt,j);
				}while (j!=v);
				add(x,cnt);add(cnt,x);
			}
		}else low[x]=min(low[x],dfn[v]);
	}
}
void dfs(int x,int fa){
	Q[++Q[0]]=x;
	f[x][0]=fa;
	for (int i=1;i<=20;++i) f[x][i]=f[f[x][i-1]][i-1];
	for (int i=hed[x];i!=-1;i=e[i].Next){
		int v=e[i].v;
		if (v==fa) continue;
		dep[v]=dep[x]+1;
		dfs(v,x);
	}
}
int lca(int x,int y){
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=20;i>=0;--i)
		if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	if (x==y) return x;
	for (int i=20;i>=0;--i)
	if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
int main(){
	Num=num=0;
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for (int i=0;i<=n+n+1;++i)
		hed[i]=-1,Hed[i]=-1;
	for (int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		Add(u,v);Add(v,u);
	}
	idx=T=1;cnt=n;
	tarjan(1);
	Q[0]=0;
	dep[1]=1;dfs(1,0);
	while (q--){
		int u,v;
		scanf("%d%d",&u,&v);
		int lc=lca(u,v);
    //cout<<lc<<" "<<f[lc][0]<<endl;
		tot[u]++;tot[v]++;
		tot[lc]--;
		tot[f[lc][0]]--;
	}
	for (int i=cnt;i>=1;--i){
		int now=Q[i];
		tot[f[now][0]]+=tot[now];
	}
	for (int i=1;i<=n;++i) printf("%d\n",tot[i]);	
	return 0;
}
