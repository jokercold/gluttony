#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
#define db long double
#define N 100500
struct node{
  ll d,p,r,g;
}mac[N];
struct yh{
  int id;
	ll g;
}c[N];
bool cmpd(node x,node y){
  if (x.d!=y.d) return x.d<y.d;
	else return x.p<y.p;
}
bool cmpg(yh x,yh y){
  return x.g<y.g;
}
ll f[N];
int q[N];
db calc(int j,int k){
	db X=(db)(f[j]-f[k]-mac[j].p+mac[j].r+mac[k].p-mac[k].r-(db)(mac[j].d+1)*mac[j].g+(db)(mac[k].d+1)*mac[k].g);
	if (mac[k].g==mac[j].g) return (X>0?1ll<<60:-1ll<<60);
	return X/(db)(mac[k].g-mac[j].g);
}
bool work(int j,int k,int i){
  return  (db)f[j]-mac[j].p+mac[j].r+(db)(mac[i].d-mac[j].d-1)*mac[j].g<=(db)f[k]-mac[k].p+mac[k].r+(db)(mac[i].d-mac[k].d-1)*mac[k].g;
}
int CC,n;
void cdq(int l,int r){
  /*cout<<l<<" "<<r<<endl;
	for (int i=1;i<=n;++i)
		  cout<<f[i]<<" ";
	cout<<endl;*/
	if (l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);
	for (int i=l;i<=mid;++i) c[i].g=mac[i].g,c[i].id=i;
	sort(c+l,c+mid+1,cmpg);
	int tail=0;
	for (int i=l;i<=mid;++i)
	if (f[c[i].id]>=mac[c[i].id].p){
		while (tail>1&&calc(q[tail-1],q[tail])>=calc(q[tail],c[i].id)) --tail;
		++tail;
		q[tail]=c[i].id;
	}
	int h=1;
	for (int i=mid+1;i<=r;++i){
	 	while (h<tail&&work(q[h],q[h+1],i)) ++h;
		int j=h;
		//if (i==6) cout<<q[j]<<endl;
		f[i]=max(f[i],f[q[j]]-mac[q[j]].p+mac[q[j]].r+(mac[i].d-mac[q[j]].d-1)*mac[q[j]].g);
	}
	cdq(mid+1,r);
}
int main(){
  //freopen("works1.in","r",stdin);
	//freopen("11.out","w",stdout);
	int DD;
	int cas=0;
	while (scanf("%d%d%d",&n,&CC,&DD)){
	  if (n==0&&CC==0&&DD==0) break;
		for (int i=1;i<=n;++i)
		  scanf("%lld%lld%lld%lld",&mac[i].d,&mac[i].p,&mac[i].r,&mac[i].g);
	  ++n;
		mac[n].d=1;
		mac[n].p=mac[n].r=mac[n].g=0;
		++n;
		mac[n].d=DD+1;
		mac[n].p=mac[n].r=mac[n].g=0;
		sort(mac+1,mac+n+1,cmpd);
		for (int i=1;i<=n;++i) f[i]=-1;
		f[1]=CC;
		cdq(1,n);
		ll ans=0;
		//cout<<"YES"<<endl;
		for (int i=1;i<=n;++i) ans=max(ans,f[i]);
		/*for (int i=1;i<=n;++i) cout<<f[i]<<" ";
		cout<<endl;*/
		++cas;
		printf("Case %d: %lld\n",cas,ans);
	}
	return 0;
}
