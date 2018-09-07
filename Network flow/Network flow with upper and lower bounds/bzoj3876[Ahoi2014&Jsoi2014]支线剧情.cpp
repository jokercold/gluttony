#include<iostream>
#include<cstdio>
using namespace std;
#define N 510
#define M 200010
int n,m,S,T,num,ans;
int du[N];
namespace Mcf{
	int vet[M],val[M],cost[M],Next[M],Fro[M];
	int hed[N],dis[N],q[N],from[N];
	bool inq[N];
	inline void add(int u,int v,int z,int w){
	  ++num;
		Fro[num]=u;
		vet[num]=v;
		val[num]=z;
		cost[num]=w;
		Next[num]=hed[u];
		hed[u]=num;
	}
	inline void addflow(int u,int v,int z,int w){
	  add(u,v,z,w);
		add(v,u,0,-w);
	}
	bool spfa(){
	  int hh=0,tt=1;
		for (int i=1;i<=T;++i) dis[i]=1<<29;
		q[hh]=S;dis[S]=0;inq[S]=true;
		while (hh!=tt){
		  int u=q[hh];
			inq[u]=false;
			++hh;
			if (hh==N-10) hh=0;
			for (int i=hed[u];i!=-1;i=Next[i]){
			  int v=vet[i];
				if (val[i]&&dis[u]+cost[i]<dis[v]){
				  dis[v]=dis[u]+cost[i];
					from[v]=i;
					if (!inq[v]){
					  inq[v]=true;
 						q[tt]=v;								
 						++tt;
						if (tt==N-10) tt=0;			
					}
				}
			}
		}
		if (dis[T]==1<<29) return 0;
		return 1;
	}
  void mcf(){
	  int flow=1<<29;
		for (int i=from[T];i;i=from[Fro[i]]){
		  flow=min(flow,val[i]);
		}
		for (int i=from[T];i;i=from[Fro[i]]){
			val[i]-=flow;
			val[i^1]+=flow;
		}
		ans+=dis[T]*flow;
	}
  void work(){
	  while (spfa()) mcf();
	}
}
void init(){
  using namespace Mcf;
	scanf("%d",&n);
	S=n+1;
	T=n+2;
	num=1;
  for (int i=1;i<=T;++i) hed[i]=-1,from[i]=0,du[i]=0;
}
void build(){
	using namespace Mcf;
  for (int i=1;i<=n;++i){
	  int tot;
		scanf("%d",&tot);
		du[i]-=tot;
	  while (tot--){
			int v,c;
		  scanf("%d%d",&v,&c);
			addflow(i,v,1<<29,c);
			++du[v];ans+=c;
		}
		if (i!=1) addflow(i,1,1<<29,0);
	}
	for (int i=1;i<=n;++i){
	  if (du[i]>0) addflow(S,i,du[i],0);
		if (du[i]<0) addflow(i,T,-du[i],0);
	}
}
int main(){
  init();
  build();
	Mcf::work();
	printf("%d\n",ans);
	return 0;
}
