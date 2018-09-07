#include<iostream>
#include<cstdio>
using namespace std;
#define M 10000
#define N 600
#define NN 10000
#define ll long long
int vet[NN],val[NN],Next[NN],hed[N];
int q[N],h[N],cur[N],a[N];
int num,S,T;
int U[NN],V[NN];
void add(int u,int v,int z){
  ++num;
	vet[num]=v;
  val[num]=z;
	Next[num]=hed[u];
	hed[u]=num;
}
void addflow(int u,int v,int z){
  add(u,v,z);
	add(v,u,0);
}
bool bfs(){
  for (int i=1;i<=T;++i) h[i]=-1;
	h[S]=0;
	int hh=0,tt=1;
	q[hh]=S;
	while (hh!=tt){
	  int u=q[hh];
		++hh;
		for (int i=hed[u];i;i=Next[i])
		if (val[i]&&h[vet[i]]==-1){
		  h[vet[i]]=h[u]+1;
			q[tt]=vet[i];
			++tt;
		}
	}
	return h[T]!=-1;
}
int dinic(int u,int low){
  if (u==T) return low;
	int used=0;
  for (int i=cur[u];i;i=Next[i])
	if (val[i]&&h[vet[i]]==h[u]+1){
	  int w=dinic(vet[i],min(low-used,val[i]));
		val[i]-=w;
		val[i^1]+=w;
		cur[u]=i;
		used+=w;
		if (used==low) return low;
	}
	if (used==0) h[u]=-1;
	return used;
}
int main(){
  int n,m;
	scanf("%d%d",&n,&m);
	ll ans1=0,ans2=0;
	for (int i=1;i<=n;++i) scanf("%d",&a[i]),ans2+=(a[i]>0)?a[i]:0;
	for (int i=1;i<=m;++i) scanf("%d%d",&U[i],&V[i]);
	for (int cas=0;cas<30;++cas){
		num=1;
		S=n+1;
		T=n+2;
		for (int i=1;i<=T;++i) hed[i]=0;
		for (int i=1;i<=n;++i)
		if (a[i]>=0){
		  if (a[i]&(1<<cas)) addflow(i,T,1<<29);
			else addflow(S,i,1<<29),addflow(S,i,1);
		}else addflow(S,i,1);
    for (int i=1;i<=m;++i){
			addflow(U[i],V[i],M);
			addflow(V[i],U[i],M);
		}
		ll ans=0;
		while (bfs()){
			for (int i=1;i<=T;++i) cur[i]=hed[i];
		  ans+=dinic(S,1<<29);
		}
		//cout<<ans<<endl;
    ans1+=(1ll<<cas)*(ans/M);
		ans2+=(1ll<<cas)*(ans%M);
	}
	printf("%lld\n%lld\n",ans1,ans2);
	return 0;
}
