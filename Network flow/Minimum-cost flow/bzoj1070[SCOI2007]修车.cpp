#include<iostream>
#include<cstdio>
using namespace std;
#define N 1010
#define M 100010
int a[70][20];
int n,m,S,T,num,ans;
namespace Mcf{
	int vet[M],val[M],cost[M],Next[M],Fro[M];
	int hed[N],dis[N],q[N],from[N];
	bool inq[N];
	void add(int u,int v,int z,int w){
	  ++num;
		Fro[num]=u;
		vet[num]=v;
		val[num]=z;
		cost[num]=w;
		Next[num]=hed[u];
		hed[u]=num;
	}
	void addflow(int u,int v,int z,int w){
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
		  ans+=flow*cost[i];
			val[i]-=flow;
			val[i^1]+=flow;
		}
	}
  void work(){
		ans=0;
	  while (spfa()) mcf();
	}
}
void init(){
  using namespace Mcf;
	scanf("%d%d",&n,&m);
	S=n*m+m+1;
	T=n*m+m+2;
	num=1;
  for (int i=1;i<=T;++i) hed[i]=-1,from[i]=0;
}
void build(){
	using namespace Mcf;
  for (int i=1;i<=m;++i)
		for (int j=1;j<=n;++j) scanf("%d",&a[i][j]);
  for (int i=1;i<=n*m;++i) addflow(S,i,1,0);
  for (int i=n*m+1;i<=n*m+m;++i) addflow(i,T,1,0);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int k=1;k<=m;++k)
				addflow((i-1)*m+j,n*m+k,1,a[k][i]*j);
}
int main(){
  init();
  build();
	Mcf::work();
	printf("%.2lf\n",(double)ans/m);
	return 0;
}
