#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
#define mp make_pair
#define fi first
#define se second
#define pr pair<ll,ll>
#define N 550000
pr tag[N<<2],mx[N<<2];
inline int read(){
  char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	return tmp;
}
void build(int p,int l,int r){
	if (l==r){    
		tag[p].fi=mx[p].fi=read();
		tag[p].se=mx[p].se=0;
		return;
	}
  int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
void cal(int x,int p){
	mx[x].fi=max(mx[x].fi,mx[p].fi+tag[x].fi);
  mx[x].se=max(mx[x].se,max(mx[p].se,mx[p].fi+tag[x].se));
  tag[x].fi=max(tag[x].fi+tag[p].fi,-1ll<<60);
	tag[x].se=max(tag[x].se+tag[p].fi,tag[p].se);
}
void pushdown(int p){
	cal(p<<1,p);  
	cal(p<<1|1,p);
  tag[p].fi=tag[p].se=mx[p].fi=mx[p].se=0;
}
void change(int p,int l,int r,int x,int y,pr TJ){
  if (l>y||r<x) return;
	if (l<r) pushdown(p);
	if (x<=l&&r<=y){
	  tag[p].fi=max(tag[p].fi+TJ.fi,-1ll<<60);
		tag[p].se=max(tag[p].se+TJ.fi,TJ.se);
    mx[p].fi=max(mx[p].fi,tag[p].fi);
		mx[p].se=max(mx[p].se,tag[p].se);
		return;
	}
	int mid=(l+r)>>1;
	change(p<<1,l,mid,x,y,TJ);
	change(p<<1|1,mid+1,r,x,y,TJ);
}
ll query(int p,int l,int r,int x,int y){
	if (l<r) pushdown(p);
  if (l==r){
	  if (y==0) return max(tag[p].fi,tag[p].se);
	  else return max(mx[p].fi,mx[p].se);
	}
	int mid=(l+r)>>1;
	if (x<=mid) return query(p<<1,l,mid,x,y);
	else return query(p<<1|1,mid+1,r,x,y);
}
int main(){
	int n,m;n=read();m=read();
	build(1,1,n);
  while (m--){
		int type=read();
		if (type==1){
		  int l=read(),r=read(),x=read();
			change(1,1,n,l,r,mp(x,-1ll<<60));
		}else if (type==2){
		  int l=read(),r=read(),x=read();
			change(1,1,n,l,r,mp(-x,0ll));
		}else if (type==3){
			int l=read(),r=read(),x=read();
		  change(1,1,n,l,r,mp(-1ll<<60,x));
		}else if (type==4){
		  int x=read();
			printf("%lld\n",query(1,1,n,x,0));
		}else{
		  int x=read();
			printf("%lld\n",query(1,1,n,x,1));
		}
	}
}
