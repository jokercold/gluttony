#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
#define ll long long
#define N 600005
int read(){
	char ch=getchar(),last='+';
	while (ch<'0'||ch>'9'){if (ch=='-') last='-';ch=getchar();}
	int tmp=0;
  while (ch>='0'&&ch<='9'){tmp=tmp*10+(ch-'0');ch=getchar();}
	if (last=='-') tmp=-tmp;
	return tmp;
}
vector<ll> G[N];
struct node{
	int ls,rs,sum;
}tr[20000005];
int rt[N];
int M,pos,n,m,Q;
int siz;
void modify(int &u,int l,int r,int k){
	if (!u) u=++siz;
	tr[u].sum++;
	if (l<r){
		int mid=(l+r)>>1;
		if (mid>=k) modify(tr[u].ls,l,mid,k);
		else modify(tr[u].rs,mid+1,r,k);
	}
}
int Query(int u,int l,int r,int k){
	if (l==r) return l;
	int mid=(l+r)>>1,siz=mid-l+1-tr[tr[u].ls].sum;
  if (k<=siz) return Query(tr[u].ls,l,mid,k);
	else return Query(tr[u].rs,mid+1,r,k-siz); 
}
ll Deal_r(int x,ll v){
	int pos=Query(rt[n+1],1,M,x);
	modify(rt[n+1],1,M,pos);
	ll ans=(pos<=n)?1ll*pos*m:G[n+1][pos-n-1];
	G[n+1].push_back(v?v:ans);
	return ans;
}
ll Deal_l(int x,int y){
	int pos=Query(rt[x],1,M,y);
	modify(rt[x],1,M,pos);
  ll ans=(pos<m)?1ll*(x-1)*m+pos:G[x][pos-m];
	G[x].push_back(Deal_r(x,ans));
	return ans;
}
int main(){
	n=read(),m=read(),Q=read();
	M=max(m,n)+Q;
	siz=0;
	while (Q--){
		int x=read(),y=read();
		if (y==m) printf("%lld\n",Deal_r(x,0));
		else printf("%lld\n",Deal_l(x,y));
	}
	return 0;
}
