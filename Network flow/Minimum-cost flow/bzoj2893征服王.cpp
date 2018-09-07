#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 3010
#define M 30100
bool map[2000][2000];
int n,m,A,B,S,T,vary,ans,num,calc;
int bl[N],Aa[N],Bb[N],Uu[M],Vv[M];
namespace Tarjan{
  int tim,tt;
	int vet[M],Next[M],stack[M];
	int dfn[N],low[N],hed[N];
	bool flag[N];
	void add(int u,int v){
	  ++num;
		vet[num]=v;
		Next[num]=hed[u];
		hed[u]=num;
	}
	void tarjan(int u){
	  ++tim;dfn[u]=low[u]=tim;
		++tt;stack[tt]=u;flag[u]=true;
		for (int i=hed[u];i!=-1;i=Next[i]){
		  int v=vet[i];
			if (!dfn[v]){
			  tarjan(v);
				low[u]=min(low[u],low[v]);
			}else if (flag[v]) low[u]=min(low[u],dfn[v]);
		}
    if (dfn[u]==low[u]){
		  ++vary;
			while (stack[tt]!=u){
			  int t=stack[tt];
				bl[t]=vary;
				flag[t]=false;
				--tt;
			}
			bl[u]=vary;
			flag[u]=false;
			--tt;
		}
	}
  void work(){
		tim=vary=tt=0;
	  for (int i=1;i<=n;++i) dfn[i]=low[i]=flag[i]=0;
	  for (int i=1;i<=n;++i)
	  if (!dfn[i]) tarjan(i);
	}
}
namespace Mcf{
	int Fro[M],vet[M],val[M],cost[M],Next[M];
	int hed[N],dis[N],q[N],from[N];
	bool inq[N];
	void add(int u,int v,int flow,int c){
	  ++num;
		Fro[num]=u;
		vet[num]=v;
		val[num]=flow;
		cost[num]=c;
		Next[num]=hed[u];
		hed[u]=num;
	}
	void addflow(int u,int v,int flow,int c){
		//cout<<u<<" "<<v<<endl;
	  add(u,v,flow,c);
		add(v,u,0,-c);
	}
	bool spfa(){
	  int hh=0,tt=1;
		for (int i=1;i<=T;++i) dis[i]=-1;
		q[hh]=S;dis[S]=0;inq[S]=true;
		while (hh!=tt){
		  int u=q[hh];
			inq[u]=false;
			++hh;
			if (hh==N-10) hh=0;
			for (int i=hed[u];i!=-1;i=Next[i]){
			  int v=vet[i];
				if (val[i]&&dis[u]+cost[i]>dis[v]){
					//cout<<v<<" "<<dis[v]<<" "<<dis[u]+cost[i]<<endl;
				  dis[v]=dis[u]+cost[i];
					from[v]=i;
					if (!inq[v]){
					  q[tt]=v;
						inq[v]=true;
						++tt;
						if (tt==N-10) tt=0;
					}
				}
			}
			//cout<<hh<<" "<<tt<<endl;
		}
    if (dis[T]==-1) return false;
		return true;
	}
	void mcf(){		
		calc=ans=0;
		while (spfa()){
			int flow=1<<29;
			for (int i=from[T];i;i=from[Fro[i]]){
				//cout<<Fro[i]<<" "<<vet[i]<<endl;
				flow=min(flow,val[i]);
			}
			++ans;
			//cout<<flow<<" "<<ans<<endl;
			for (int i=from[T];i;i=from[Fro[i]]){
        calc+=flow*cost[i];
			  val[i]-=flow;
				val[i^1]+=flow;
			}
			if (calc==vary) break;
		}
	}
}
void init(){
  scanf("%d%d%d%d",&n,&m,&A,&B);
	for (int i=1;i<=A;++i) scanf("%d",&Aa[i]);
	for (int i=1;i<=B;++i) scanf("%d",&Bb[i]);
	num=1;
	using namespace Tarjan;
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=1;i<=m;++i){
		scanf("%d%d",&Uu[i],&Vv[i]);
		add(Uu[i],Vv[i]);
	}
}
void build(){
	using namespace Mcf;
	num=1;
  S=vary+vary+1;
	T=vary+vary+2;
	memset(map,0,sizeof(map));
	for (int i=0;i<=T;++i) hed[i]=-1,from[i]=0;
  for (int i=1;i<=A;++i) addflow(S,bl[Aa[i]],1<<29,0);
	for (int i=1;i<=B;++i) addflow(bl[Bb[i]]+vary,T,1<<29,0);
	for (int i=1;i<=m;++i)
	if (bl[Uu[i]]!=bl[Vv[i]]&&map[bl[Uu[i]]][bl[Vv[i]]]==false) 
		addflow(bl[Uu[i]]+vary,bl[Vv[i]],1<<29,0),map[bl[Uu[i]]][bl[Vv[i]]]=true;
	for (int i=1;i<=vary;++i) addflow(i,i+vary,1,1),addflow(i,i+vary,1<<29,0);
}
int main(){
  int cas;
  scanf("%d",&cas);
  while (cas--){
		init();
		Tarjan::work();
	  //cout<<vary<<endl;
		build();
	  Mcf::mcf();
		//cout<<calc<<endl;
		if (calc!=vary) printf("no solution\n");
		else printf("%d\n",ans);
	}
	return 0;
}
