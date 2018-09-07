#include<iostream>
#include<cstdio>
using namespace std;
#define N 6000500
int n,m,lim;
int sz;
int sum[N],ls[N],rs[N];
int root[400000];
void update(int l,int r,int x,int &y,int v){
  y=++sz;
	sum[y]=sum[x]+1;
	if (l==r) return;
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if (v<=mid) update(l,mid,ls[x],ls[y],v);
	else update(mid+1,r,rs[x],rs[y],v);
}
int query(int L,int R){
  int l=1,r=lim;
	int x=root[L-1],y=root[R];
	int tmp=(R-L+1)>>1;
	while (l!=r){
		//cout<<sum[x]<<" "<<sum[y]<<" "<<tmp<<endl;
	  if (sum[y]-sum[x]<=tmp) return 0;
		int mid=(l+r)>>1;
		if (sum[ls[y]]-sum[ls[x]]>tmp){
		  r=mid;x=ls[x];y=ls[y];
		}else if (sum[rs[y]]-sum[rs[x]]>tmp){
		  l=mid+1;x=rs[x];y=rs[y];
		}else return 0;
	}
	return l;
}
int main(){ 
	sz=0;
	scanf("%d",&n);
	scanf("%d",&lim);
	for (int i=1;i<=n;++i){
	  int v;
		scanf("%d",&v);
		update(1,lim,root[i-1],root[i],v);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
	  int l,r;
		scanf("%d%d",&l,&r);
		int ans=query(l,r);
		if (ans==0) printf("no\n");
		else printf("yes %d\n",ans);
	}
	return 0;
}
