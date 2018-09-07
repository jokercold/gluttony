#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define M 201314
#define N 60000
int num,m,cnt,n;
int tree[N*4],tag[N*4],dep[N],f[N],siz[N],son[N],id[N],top[N],ans[N],hed[N],Next[N*2],vet[N*2];
bool visit[N];
struct node{
  int id,x,type,z;
}q[N*2];
bool cmp(node x,node y){
  return x.x<y.x;
}
void add(int u,int v){
  ++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
void dfs1(int u,int fa){
	visit[u]=true;
	dep[u]=dep[fa]+1;
	f[u]=fa;
	siz[u]=1;
	son[u]=0;
  for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (visit[v]) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if (siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int ancestor){
	visit[u]=true;
  id[u]=++cnt;
	top[u]=ancestor;
  if (son[u]) dfs2(son[u],ancestor);
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (visit[v]) continue;
		dfs2(v,v);
	}
}
void pushdown(int p,int l,int r){
	int mid=(l+r)>>1;
  tree[p<<1]+=tag[p]*(mid-l+1);
	tag[p<<1]+=tag[p];
	tree[p<<1|1]+=tag[p]*(r-mid);
	tag[p<<1|1]+=tag[p];
	tag[p]=0;
}
void T_change(int p,int l,int r,int x,int y){
  if (x>r||y<l) return;
	if (tag[p]&&l<r) pushdown(p,l,r);
	if (x<=l&&r<=y){
	  tree[p]+=(r-l+1);
		tag[p]+=1;
		return;
	}
	int mid=(l+r)>>1;
	T_change(p<<1,l,mid,x,y);
	T_change(p<<1|1,mid+1,r,x,y);
  tree[p]=tree[p<<1]+tree[p<<1|1];
}
void change(int x){
  while (top[x]!=1){
	  T_change(1,1,n,id[top[x]],id[x]);
		x=f[top[x]];
	}
	T_change(1,1,n,id[top[x]],id[x]);
}
int T_query(int p,int l,int r,int x,int y){
  if (x>r||y<l) return 0;
	if (tag[p]&&l<r) pushdown(p,l,r);
	if (x<=l&&r<=y) return tree[p];
	int mid=(l+r)>>1;
	return T_query(p<<1,l,mid,x,y)+T_query(p<<1|1,mid+1,r,x,y);
}
int query(int x){
  int ans=0;
	while (top[x]!=1){
		ans+=T_query(1,1,n,id[top[x]],id[x]);
		ans%=M;
		x=f[top[x]];
	}
	ans+=T_query(1,1,n,id[top[x]],id[x]);
	ans%=M;
	return ans;
}
int main(){
  int Q;
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=2;i<=n;++i){
	  int u;
		scanf("%d",&u);
		++u;
	  add(i,u);
		add(u,i);
	}
	for (int i=1;i<=n;++i) visit[i]=false;
	dfs1(1,0);
	cnt=0;
	for (int i=1;i<=n;++i) visit[i]=false;
	dfs2(1,1);
	int m=0;
	for (int i=1;i<=Q;++i){
	  int l,r,z;
		scanf("%d%d%d",&l,&r,&z);
		++l;++r;++z;
		q[++m]=(node){i,l-1,-1,z};
		q[++m]=(node){i,r,1,z};
	}
  sort(q+1,q+m+1,cmp);
	int now=0;
	for (int i=1;i<=m;++i){
	  while (now<q[i].x){
			++now;
		  change(now);
		}
		ans[q[i].id]+=q[i].type*query(q[i].z);
		ans[q[i].id]%=M;
	}
	for (int i=1;i<=Q;++i) printf("%d\n",(ans[i]+M)%M);
	return 0;
}
