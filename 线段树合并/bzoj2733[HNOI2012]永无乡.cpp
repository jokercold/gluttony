#include<cstdio>
#include<iostream>
using namespace std;
char ch[30];
int cnt;
#define N 200000
int v[N],fa[N],id[N],sum[N*10],root[N],ls[N*10],rs[N*10];
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
int find(int x){
  if (fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
int query(int k,int l,int r,int x){
  if (l==r) return l;
	int mid=(l+r)>>1;
	if (sum[ls[k]]>=x) return query(ls[k],l,mid,x);
  else return query(rs[k],mid+1,r,x-sum[ls[k]]);
}
int merge(int x,int y){
  if (x==0||y==0) return x+y;
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	sum[x]=sum[ls[x]]+sum[rs[x]];
  return x;
}
int main(){
	cnt=0;
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&v[i]),fa[i]=i;
	for (int i=1;i<=m;++i){
	  int u,v;
		scanf("%d%d",&u,&v);
		int roota=find(u);
		int rootb=find(v);
    if (roota!=rootb) fa[roota]=rootb;
	}
	for (int i=1;i<=n;++i){
	  insert(root[find(i)],1,n,v[i]);
		id[v[i]]=i;
	}
	int q;
	scanf("%d",&q);
  for (int i=1;i<=q;++i){
	  scanf("%s",ch);
		if (ch[0]=='Q'){
		  int x,k;
			scanf("%d%d",&x,&k);
			int rootx=find(x);
			//cout<<"&&&&&&&&&&  "<<sum[root[rootx]]<<" &&&&&&&&&&&"<<endl;
			if (sum[root[rootx]]<k){
			  printf("-1\n");
				continue;
			}
			int y=query(root[rootx],1,n,k);
			printf("%d\n",id[y]);
		}else{
		  int x,y;
			scanf("%d%d",&x,&y);
			int rootx=find(x),rooty=find(y);
			if (rootx!=rooty){
				fa[rootx]=rooty;
			  root[rootx]=merge(root[rooty],root[rootx]);
			}
		}
	}
	return 0;
}
