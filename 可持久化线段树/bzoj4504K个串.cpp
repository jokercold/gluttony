#include<iostream>
#include<cstdio>
#include<map>
#include<queue>
using namespace std;
#define mp(a,b,c,d,e) (node){a,b,c,d,e}
#define ll long long
typedef pair<ll,int>pr;
#define mpr(a,b) make_pair(a,b)
map<int,int>pre;
struct node{int i,l,r,v;ll key;};
inline bool operator<(node x,node y){
  return x.key<y.key;
}
priority_queue<node,vector<node> >q;
#define N 100010 
#define M 7000000
pr tree[M];
int ls[M],rs[M],root[M];
ll tag[M];
int sz;
void build(int &y,int l,int r){
  y=++sz;
	if (l==r){
		tree[y]=pr(0,l);
		tag[y]=0;
		return;
	}
	int mid=(l+r)>>1;
	build(ls[y],l,mid);
	build(rs[y],mid+1,r);
	tree[y]=pr(0,0);
	tag[y]=0;
}
void update(int x){
  int l=ls[x],r=rs[x];
	if (tree[l].first+tag[l]>tree[r].first+tag[r])
	tree[x]=mpr(tree[l].first+tag[l],tree[l].second);
	else tree[x]=mpr(tree[r].first+tag[r],tree[r].second);
}
void change(int x,int &y,int l,int r,int qx,int qy,int z){
  y=++sz;
	tree[y]=tree[x];
	tag[y]=tag[x];
  ls[y]=ls[x];rs[y]=rs[x];
	if (l==qx&&r==qy){
		tag[y]+=z;
		return;
	}
	int mid=(l+r)>>1;
	if (qy<=mid) change(ls[x],ls[y],l,mid,qx,qy,z);
	else if (qx>=mid+1) change(rs[x],rs[y],mid+1,r,qx,qy,z);
	else{
	  change(ls[x],ls[y],l,mid,qx,mid,z);
		change(rs[x],rs[y],mid+1,r,mid+1,qy,z);
	}
  update(y);	
}
pr query(int p,int l,int r,int qx,int qy){
	//cout<<p<<" "<<l<<" "<<r<<" "<<tree[p].first<<" "<<tree[p].second<<endl;
  if (l==qx&&r==qy) return mpr(tree[p].first+tag[p],tree[p].second);
	int mid=(l+r)>>1;
	pr t;
	if (qy<=mid) t=query(ls[p],l,mid,qx,qy);
	else if (qx>=mid+1) t=query(rs[p],mid+1,r,qx,qy);
	else t=max(query(ls[p],l,mid,qx,mid),query(rs[p],mid+1,r,mid+1,qy));
	return mpr(t.first+tag[p],t.second);
}
int main(){
	sz=0;
  int n,K;
	scanf("%d%d",&n,&K);
	build(root[0],1,n);
	//cout<<"YESover"<<endl;
	for (int i=1;i<=n;++i){
	  int x;
		scanf("%d",&x);
    change(root[i-1],root[i],1,n,pre[x]+1,i,x);
		//cout<<x<<": "<<pre[x]<<" "<<i<<endl;
		pre[x]=i;
	}
	//cout<<"YESone"<<endl;
	for (int i=1;i<=n;++i){
		pr x=query(root[i],1,n,1,i);
		//cout<<i<<" "<<x.first<<" "<<x.second<<endl;
		q.push(mp(i,1,i,x.second,x.first));
	}
	//cout<<"YES"<<endl;
	node ans;
	for (int i=1;i<=K;++i){
	  ans=q.top();q.pop();
	  if (ans.v>ans.l){
			pr x=query(root[ans.i],1,n,ans.l,ans.v-1);
      q.push(mp(ans.i,ans.l,ans.v-1,x.second,x.first));
		}
		if (ans.v<ans.r){
		  pr x=query(root[ans.i],1,n,ans.v+1,ans.r);
			q.push(mp(ans.i,ans.v+1,ans.r,x.second,x.first));
		}
		//printf("%lld\n",ans.key);
	}
	printf("%lld\n",ans.key);
	return 0;
}
