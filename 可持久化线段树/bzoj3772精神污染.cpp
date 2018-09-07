#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
#define N 100005
#define ll long long
int root[N],ls[N*40],rs[N*40],sum[N*40];
int hed[N],vet[N*2],Next[N*2];
int f[N][18],dep[N];
int in[N],out[N];
vector<int> Q[N];
struct node{
  int x,y;
}q[N];
ll gcd(ll x,ll y){if (y==0) return x;else return gcd(y,x%y);}
int id,num,sz,n;
void add(int u,int v){
  ++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
int lca(int u,int v){
	if (dep[u]<dep[v]) swap(u,v);
	for (int i=17;i>=0;--i)
	if (dep[f[u][i]]>=dep[v]) u=f[u][i];
	if (u==v) return u;
	for (int i=17;i>=0;--i)
	if (f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
int insert(int x,int l,int r,int z,int val){
	int y=++sz;
	sum[y]=sum[x]+val;
	ls[y]=ls[x];rs[y]=rs[x];
	if (l==r) return y;
	int mid=(l+r)>>1;
	if (z<=mid) ls[y]=insert(ls[y],l,mid,z,val);
	else rs[y]=insert(rs[y],mid+1,r,z,val);
	return y;
}
int query(int u,int v,int a,int b,int l,int r,int x,int y){
 	if (l==x&&r==y) return sum[u]+sum[v]-sum[a]-sum[b];
	int mid=(l+r)>>1;
	if (y<=mid) return query(ls[u],ls[v],ls[a],ls[b],l,mid,x,y);
	if (x>=mid+1) return query(rs[u],rs[v],rs[a],rs[b],mid+1,r,x,y);
	return query(ls[u],ls[v],ls[a],ls[b],l,mid,x,mid)+query(rs[u],rs[v],rs[a],rs[b],mid+1,r,mid+1,y);
}
void dfs1(int u,int fa){
  f[u][0]=fa;
	dep[u]=dep[fa]+1;
	in[u]=++id;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fa) continue;
		dfs1(v,u);
	}
  out[u]=++id;
}
void dfs2(int u,int fa){
	root[u]=root[f[u][0]];
  for (int i=0;i<Q[u].size();++i){
		root[u]=insert(root[u],1,id,in[Q[u][i]],1);
		root[u]=insert(root[u],1,id,out[Q[u][i]],-1);
	}
  for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fa) continue;
		dfs2(v,u);
	}
}
int main(){
  int m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=1;i<n;++i){
	  int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for (int i=1;i<=m;++i){
	  scanf("%d%d",&q[i].x,&q[i].y);
		Q[q[i].x].push_back(q[i].y);
	}
	id=0;
	dfs1(1,0);
	for (int i=1;i<=17;++i)
		for (int j=1;j<=n;++j)
		f[j][i]=f[f[j][i-1]][i-1];
	dfs2(1,0);
	ll ans=0;
  for (int i=1;i<=m;++i){
		int u=q[i].x,v=q[i].y;
		int a=lca(u,v),b=f[a][0];
		//cout<<u<<" "<<v<<" "<<a<<" "<<b<<" "<<in[a]<<" "<<in[v]<<endl;
	  ans+=query(root[u],root[v],root[a],root[b],1,id,in[a],in[v]);
		ans+=query(root[u],root[v],root[a],root[b],1,id,in[a],in[u]);
		ans-=query(root[u],root[v],root[a],root[b],1,id,in[a],in[a]);
		ans--;
		//cout<<ans<<endl;
	}
	ll deno=(ll)m*(m-1)/2;
	ll t=gcd(ans,deno);
	printf("%lld/%lld\n",ans/t,deno/t);
	return 0;
}
