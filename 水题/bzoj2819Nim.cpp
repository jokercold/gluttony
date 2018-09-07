#include<iostream>
#include<cstdio>
using namespace std;
#define N 501000
int fa[N][25];
int dep[N],a[N];
int h[N],l[N],r[N],hed[N],vet[N*2],Next[N*2];
int num,cnt,n;
#define lowbit(x) ((x)&(-x))
void modify(int x,int v){
  for (int i=x;i<=n;i+=lowbit(i))
		h[i]^=v;
}
int sum(int x){
  int tmp=0;
	for (int i=x;i>0;i-=lowbit(i))
		tmp^=h[i];
	return tmp;
}
void add(int u,int v){
  ++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
void dfs(int u,int fath){
  fa[u][0]=fath;
	dep[u]=dep[fath]+1;
	l[u]=++cnt;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fath) continue;
		dfs(v,u);
	}
	r[u]=cnt;
}
int lca(int x,int y){
  if (dep[x]<dep[y]) swap(x,y);
	for (int i=19;i>=0;--i)
	if (dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if (x==y) return x;
	for (int i=19;i>=0;--i)
	if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main(){
	scanf("%d",&n);
	num=0;
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	for (int i=1;i<n;++i){
	  int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	cnt=0;
	dfs(1,0);
	for (int j=1;j<=19;++j)
		for (int i=1;i<=n;++i)
		fa[i][j]=fa[fa[i][j-1]][j-1];
	for (int i=1;i<=n;++i)
		modify(l[i],a[i]),modify(r[i]+1,a[i]);
	int q;
	scanf("%d",&q);
	while (q--){
	  char opt[10];
		scanf("%s",opt);
		if (opt[0]=='Q'){
		  int x,y;
			scanf("%d%d",&x,&y);
			int z=lca(x,y);
			int ans=sum(l[x])^sum(l[y])^a[z];
			if (ans) printf("Yes\n");
			else printf("No\n");
		}else{
		  int x,y;
			scanf("%d%d",&x,&y);
			modify(l[x],a[x]);modify(r[x]+1,a[x]);
			a[x]=y;
			modify(l[x],a[x]);modify(r[x]+1,a[x]);
		}
	}
	return 0;
}
