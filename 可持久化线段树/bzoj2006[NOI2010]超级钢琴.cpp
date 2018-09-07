#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
#define mp(a,b,c,d) (node){a,b,c,d}
#define ll long long
#define N 500005
struct node{int i,l,r,t;};
int bin[20],log[N];
int a[N],mx[N][20];
ll ans;
int n,K,L,R;
void pre(){
  log[0]=-1;
	for (int i=1;i<=n;++i) log[i]=log[i>>1]+1;
	for (int i=1;i<=n;++i) mx[i][0]=i;
	for (int i=n;i;i--)
		for (int j=1;j<=18;++j)
		if (i+bin[j]-1<=n){
			int t1=mx[i][j-1],t2=mx[i+bin[j-1]][j-1];
			mx[i][j]=a[t1]>a[t2]?t1:t2;
		}else break;
}
inline int query(int l,int r){
  if (l==r) return l;
	int t=log[r-l+1];
	int t1=mx[l][t],t2=mx[r-bin[t]+1][t];
	return a[t1]>a[t2]?t1:t2;
}
inline bool operator<(node x,node y){
  return a[x.t]-a[x.i-1]<a[y.t]-a[y.i-1];
}
void solve(){
  priority_queue<node,vector<node> > q;
	for (int i=1;i<=n;++i)
	if (i+L-1<=n){
	  int t=min(n,i+R-1);
		q.push(mp(i,i+L-1,t,query(i+L-1,t)));
	}
	for (int i=1;i<=K;++i){
	  node t=q.top();q.pop();
		ans+=a[t.t]-a[t.i-1];
		if (t.t>t.l) q.push(mp(t.i,t.l,t.t-1,query(t.l,t.t-1)));
		if (t.t<t.r) q.push(mp(t.i,t.t+1,t.r,query(t.t+1,t.r)));
	}
}
int main(){
	bin[0]=1;for (int i=1;i<20;++i) bin[i]=bin[i-1]<<1;
	scanf("%d%d%d%d",&n,&K,&L,&R);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	for (int i=1;i<=n;++i) a[i]+=a[i-1];
	pre();
	solve();
	printf("%lld\n",ans);
	return 0;
}
