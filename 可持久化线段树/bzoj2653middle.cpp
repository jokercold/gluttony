#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 200500
struct node{
  int x,id;
}list[N];
bool cmp(node x,node y){
  return x.x<y.x;
}
int sz,n;
int q[10];
struct yh{
  int l,r,sum;
}tree[N*20];
int ls[N*20],rs[N*20],root[N*20];
void update(int x){
  int l=ls[x],r=rs[x];
	tree[x].sum=tree[l].sum+tree[r].sum;
	tree[x].l=max(tree[l].l,tree[l].sum+tree[r].l);
	tree[x].r=max(tree[r].r,tree[r].sum+tree[l].r);
}
void build(int &x,int l,int r){
  x=++sz;
	if (l==r){
	  tree[x].l=tree[x].r=tree[x].sum=1;
		return;
	}
	int mid=(l+r)>>1;
	build(ls[x],l,mid);
	build(rs[x],mid+1,r);
	update(x);
}
void insert(int x,int &y,int l,int r,int z,int v){
  y=++sz;
	if (l==r){
	  tree[y].l=tree[y].r=tree[y].sum=v;
		return;
	}
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if (mid>=z) insert(ls[x],ls[y],l,mid,z,v);
	else insert(rs[x],rs[y],mid+1,r,z,v);
	update(y);
}
int Query(int p,int l,int r,int x,int y){
  if (l>r) return 0;
  if (l==x&&r==y) return tree[p].sum;
  int mid=(l+r)>>1;
  if (y<=mid) return Query(ls[p],l,mid,x,y);
  if (x>=mid+1) return Query(rs[p],mid+1,r,x,y);
	return Query(ls[p],l,mid,x,mid)+Query(rs[p],mid+1,r,mid+1,y);
}
int Query_L(int p,int l,int r,int x,int y){ 
	if (l>r) return 0;
	if (l==x&&r==y) return tree[p].l;
	int mid=(l+r)>>1;
	if (y<=mid) return Query_L(ls[p],l,mid,x,y);
	if (x>=mid+1) return Query_L(rs[p],mid+1,r,x,y);
	return max(Query_L(ls[p],l,mid,x,mid),Query(ls[p],l,mid,x,mid)+Query_L(rs[p],mid+1,r,mid+1,y));
}
int Query_R(int p,int l,int r,int x,int y){
	if (l>r) return 0;
  if (l==x&&r==y) return tree[p].r;
	int mid=(l+r)>>1;
	if (y<=mid) return Query_R(ls[p],l,mid,x,y);
	if (x>=mid+1) return Query_R(rs[p],mid+1,r,x,y);
	return max(Query_R(ls[p],l,mid,x,mid)+Query(rs[p],mid+1,r,mid+1,y),Query_R(rs[p],mid+1,r,mid+1,y));
}
bool check(int mid){
	/*cout<<Query(root[mid],1,n,q[1],q[2])<<" ";
	cout<<max(0,Query_R(root[mid],1,n,q[0],q[1]-1))<<" ";
	cout<<max(0,Query_L(root[mid],1,n,q[2]+1,q[3]))<<endl;*/
	return (Query(root[mid],1,n,q[1],q[2])+max(0,Query_R(root[mid],1,n,q[0],q[1]-1))+max(0,Query_L(root[mid],1,n,q[2]+1,q[3])))>=0;
}
int main(){	
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d",&list[i].x),list[i].id=i;
  sort(list+1,list+n+1,cmp);
	sz=0;
	build(root[1],1,n);
  for (int i=2;i<=n;++i) insert(root[i-1],root[i],1,n,list[i-1].id,-1);
	int Q;
	scanf("%d",&Q);
	int ans=0;
	while (Q--){
		//cout<<ans<<endl;
	  for (int i=0;i<4;++i){
			scanf("%d",&q[i]);;
		  q[i]=(q[i]+ans)%n;
			++q[i];
		}
		sort(q,q+4);
		//cout<<check(5)<<endl;
		int l=1,r=n;ans=0;
		while (l<=r){
		  int mid=(l+r)>>1;
			if (check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		ans=list[ans].x;
		printf("%d\n",ans);
	}
	return 0;
}
