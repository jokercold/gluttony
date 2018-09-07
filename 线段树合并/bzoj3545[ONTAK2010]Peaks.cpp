#include<stdio.h>
#include<algorithm>
using namespace std;
#define M 600500
#define N 100500
int cnt;
inline int read(){
  int x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
  return x*f;
}
int ls[M*10],rs[M*10],sum[M*10],root[N],a[N],h[N],fa[N],ans[M];
struct node{
  int u,v,c,id;
}edge[M],Q[M];
bool cmp(node x,node y){
  return x.c<y.c;
}
int find(int x){
  if (fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
void insert(int &k,int l,int r,int x){
  if (!k) k=++cnt;
	if (l==r){
	  sum[k]=1;
		return;
	}
  int mid=(l+r)>>1;
	if (mid>=x) insert(ls[k],l,mid,x);
	else insert(rs[k],mid+1,r,x);
	sum[k]=sum[ls[k]]+sum[rs[k]];
}
int query(int k,int l,int r,int x){
  if (l==r) return l;
	int mid=(l+r)>>1;
	if (sum[ls[k]]>=x) return query(ls[k],l,mid,x);
	else return query(rs[k],mid+1,r,x-sum[ls[k]]);
}
int merge(int x,int y){
  if (x==0||y==0) return x+y;
	if (!ls[x]&&!rs[x]){
	  sum[x]=sum[x]+sum[y];
		return x;
	}
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	sum[x]=sum[ls[x]]+sum[rs[x]];
	return x;
}
void MERGE(int u,int v){
  int ufa=find(u);
	int vfa=find(v);
	if (ufa==vfa) return;
	fa[ufa]=vfa;
	root[ufa]=merge(root[vfa],root[ufa]);
}
int main(){
	cnt=0;
  int n,m,q;
	n=read();m=read();q=read();
	for (int i=1;i<=n;++i) h[i]=read(),a[i]=h[i];
	sort(a+1,a+n+1);
	for (int i=1;i<=n;++i) h[i]=lower_bound(a+1,a+n+1,h[i])-a;
	for (int i=1;i<=n;++i){
		fa[i]=i;	
		//cout<<h[i]<<endl;
	  insert(root[i],1,n,h[i]);
	}
	for (int i=1;i<=m;++i)
	  edge[i].u=read(),edge[i].v=read(),edge[i].c=read();
	for (int i=1;i<=q;++i)
		Q[i].u=read(),Q[i].c=read(),Q[i].v=read(),Q[i].id=i;
	sort(edge+1,edge+m+1,cmp);
	sort(Q+1,Q+q+1,cmp);
	int h=1;
	for (int i=1;i<=q;++i){
	  while (h<=m&&edge[h].c<=Q[i].c){
		  MERGE(edge[h].u,edge[h].v);
			//cout<<edge[h].u<<" "<<edge[h].v<<endl;
			++h;
		}
		int rootx=find(Q[i].u);	
		//cout<<rootx<<endl;
		if (sum[root[rootx]]<Q[i].v){
		  ans[Q[i].id]=-1;
		  continue;
		}
		Q[i].v=sum[root[rootx]]-Q[i].v+1;
		int y=query(root[rootx],1,n,Q[i].v);
		ans[Q[i].id]=a[y];
	}
	for (int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
