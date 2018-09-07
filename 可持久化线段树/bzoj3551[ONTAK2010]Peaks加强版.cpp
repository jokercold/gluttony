#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
  int x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
  return x*f;
}
#define NM 110000
struct node{
  int u,v,z;
}edge[510000];
bool vis[NM<<1];
int vet[NM<<1],Next[NM<<1],hed[NM<<1],val[NM<<1],q[NM<<2];
int fath[NM<<1],fa[NM<<1][20],mx[NM<<1][20];
int dep[NM<<1],cc[NM],h[NM],st[NM<<1],ed[NM<<1];
int root[NM*20],ls[NM*20],rs[NM*20],sum[NM*20];
bool cmp(node x,node y){
  return x.z<y.z;
}
int num;
void add(int u,int v){
  ++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
int n,m,Q;
int find(int x){
  return x==fath[x]?x:fath[x]=find(fath[x]);
}
int lca(int x,int val){
  for (int i=17;i>=0;--i)
	if (dep[x]>=(1<<i)&&mx[x][i]<=val) x=fa[x][i];
	return x;
}
int top;
void dfs(int x){
  vis[x]=true;q[++top]=x;
	for (int i=hed[x];i!=-1;i=Next[i]){
	  int v=vet[i];
		dep[v]=dep[x]+1;
		mx[v][0]=val[x];
		fa[v][0]=x;
    dfs(v);
	}
	if (x>n) q[++top]=x;
}
int sz;
void insert(int x,int &y,int l,int r,int val){
  y=++sz;
	sum[y]=sum[x]+1;
	if (l==r) return;
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if (val<=mid) insert(ls[x],ls[y],l,mid,val);
	else insert(rs[x],rs[y],mid+1,r,val);
}
int query(int x,int y,int l,int r,int k){
	//cout<<k<<endl;
  if (l==r) return l;
	int mid=(l+r)>>1;
	int S=sum[ls[y]]-sum[ls[x]];
	if (S>=k) return query(ls[x],ls[y],l,mid,k);
	else return query(rs[x],rs[y],mid+1,r,k-S); 
}
void build(){
  sort(edge+1,edge+m+1,cmp);
	int nnew=n;
	for (int i=1;i<=n+n;++i) hed[i]=-1;
	for (int i=1;i<=n+n;++i) fath[i]=i,val[i]=0;
	for (int i=1;i<=m;++i){
	  int rotu=find(edge[i].u);
		int rotv=find(edge[i].v);
		if (rotu==rotv) continue;
		++nnew;
		fath[rotu]=nnew;
		fath[rotv]=nnew;
		val[nnew]=edge[i].z;
		add(nnew,rotu);add(nnew,rotv);
		if (nnew==n+n+1) break;
	}
  for (int i=1;i<=n;++i) 
	if (!vis[i]) dfs(find(i));
	for (int j=1;j<=17;++j)
	  for (int i=1;i<=n+n-1;++i){
		  fa[i][j]=fa[fa[i][j-1]][j-1];
			mx[i][j]=max(mx[i][j-1],mx[fa[i][j-1]][j-1]);
		}
	for (int i=1;i<=top;++i){
	  int t=q[i];
		if (t<=n) insert(root[i-1],root[i],1,n,h[t]);
		else{
		  root[i]=root[i-1];
			if (!st[t]) st[t]=i;
			else ed[t]=i;
		}
	}
}
void solve(){
	int lastans=-1;
  while (Q--){
	  int v=read(),x=read(),k=read();
		if (lastans!=-1) v^=lastans,x^=lastans,k^=lastans;
		int t=lca(v,x);
    int l=root[st[t]],r=root[ed[t]];
		if (sum[r]-sum[l]<k) lastans=-1;
		else lastans=cc[query(l,r,1,n,sum[r]-sum[l]-k+1)];
		printf("%d\n",lastans);
	}
}
int main(){	
	n=read();m=read();Q=read();
	for (int i=1;i<=n;++i) h[i]=read(),cc[i]=h[i];
	sort(cc+1,cc+n+1);
  for (int i=1;i<=n;++i) h[i]=lower_bound(cc+1,cc+n+1,h[i])-cc;
	for (int i=1;i<=m;++i) edge[i].u=read(),edge[i].v=read(),edge[i].z=read();
 	build();
	solve();
	return 0;
}
