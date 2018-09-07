#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 105000
#define M 2050000
int sz,n1,num;
int f[N][20],A[N],B[N];
int dep[N],hed[N];
int vet[N*2],Next[N*2],root[N];
int sum[M],ls[M],rs[M];
void add(int u,int v){
	++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
void update(int l,int r,int x,int &y,int v){
  ++sz;
	y=sz;
	sum[y]=sum[x]+1;
	if (l==r) return;
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if (v<=mid) update(l,mid,ls[x],ls[y],v);
	else update(mid+1,r,rs[x],rs[y],v);
}
void dfs(int x,int fa){
	f[x][0]=fa;
	dep[x]=dep[fa]+1;
	update(1,n1,root[fa],root[x],A[x]);
	for (int i=hed[x];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fa) continue;
		dfs(v,x);
	}
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
int query(int u,int v,int k){
	int a=u,b=v;
	int c=lca(u,v),d=f[c][0];
  a=root[a];b=root[b];c=root[c],d=root[d];
	int l=1,r=n1;
	while (l<r){
	  int Sum=sum[ls[a]]+sum[ls[b]]-sum[ls[c]]-sum[ls[d]];
		int mid=(l+r)>>1;
		if (Sum>=k){
      a=ls[a];b=ls[b];c=ls[c];d=ls[d];
			r=mid;
		}else{
			l=mid+1;
			k-=Sum;
		  a=rs[a];b=rs[b];c=rs[c];d=rs[d];
		}
	}
	return B[l];
}
int main(){
	num=0;
  int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) hed[i]=-1;
	n1=n;
	for (int i=1;i<=n;++i){
		scanf("%d",&A[i]);
	  B[i]=A[i];
	}
	sort(B+1,B+n1+1);
  n1=unique(B+1,B+n1+1)-B-1;
	for (int i=1;i<=n;++i)
	  A[i]=lower_bound(B+1,B+n1+1,A[i])-B;
	for (int i=1;i<n;++i){
	  int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dep[0]=0;
	dfs(1,0);
	for (int j=1;j<=17;++j)
		for (int i=1;i<=n;++i)
		f[i][j]=f[f[i][j-1]][j-1];
	sz=0;
  int ans=0;
	while (m--){
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
    u=u^ans;
		ans=query(u,v,k);
	  printf("%d",ans);
		if(m) printf("\n");
	}
	return 0;
}
