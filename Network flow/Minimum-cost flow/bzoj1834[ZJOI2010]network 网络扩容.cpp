#include<iostream>
#include<cstdio>
using namespace std;
#define M 100100
#define N 2010
int n,m,KK,num,S,T,ans;
int tim[M],vet[M],val[M],cost[M],Next[M],Fro[M];
int hed[N];
void add(int u,int v,int z,int w,int kind){
	++num;
	Fro[num]=u;
	vet[num]=v;
	val[num]=z;
	if (kind==0){
		tim[num]=w;
	  cost[num]=0;
	}else cost[num]=w;
	Next[num]=hed[u];
	hed[u]=num;
}
void addflow(int u,int v,int z,int w,int kind){
	add(u,v,z,w,kind);
	add(v,u,0,-w,kind);
}
namespace Dinic{
	int q[N],h[N],cur[N];
	bool bfs(){
		int tt=1,hh=1;
		for (int i=0;i<=T;++i) h[i]=-1;
		q[1]=S;h[S]=0;
		while (hh<=tt){
			int u=q[hh];
			++hh;
			for (int i=hed[u];i!=-1;i=Next[i])
			if (val[i]&&h[vet[i]]==-1){
				++tt;
				q[tt]=vet[i];
				h[vet[i]]=h[u]+1;
			}
		}
		return h[T]!=-1;
	}
	int dfs(int u,int low){
		if (u==T) return low;
		int used=0;
		for (int i=cur[u];i!=-1;i=Next[i]){
			int v=vet[i];
			if (h[v]==h[u]+1&&val[i]){
				int w=dfs(v,min(val[i],low-used));
				val[i]-=w;
				val[i^1]+=w;
				used+=w;
				cur[u]=i;
				if (used==low) return low;
			}
		}
		if (used==0) h[u]=-1;
		return used;
	}
	void dinic(){
		ans=0;
		while (bfs()){
			for (int i=0;i<=T;++i) cur[i]=hed[i];
			ans+=dfs(S,1<<29);
		  //cout<<ans<<endl;
		}
	}
}
namespace Mcf{
	int q[N],dis[N],from[N];
	bool inq[N];
	bool spfa(){
	  int hh=0,tt=1;
		for (int i=0;i<=T;++i) dis[i]=1<<29;
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
		//cout<<1<<endl;
	}
  void work(){
	  while (spfa()) mcf();
	}
}
void init(){	
	scanf("%d%d%d",&n,&m,&KK);
	S=1;
	T=n;
	num=1;
  for (int i=0;i<=T;++i) hed[i]=-1;
	using namespace Mcf;
	for (int i=0;i<=T;++i) from[i]=0,inq[i]=false;
}
void build(){  
	for (int i=1;i<=m;++i){
	  int u,v,c,w;
		scanf("%d%d%d%d",&u,&v,&c,&w);
		addflow(u,v,c,w,0);
	}
	//cout<<"YES"<<endl;
}
int main(){
  init();
  build();
	Dinic::dinic();
	printf("%d ",ans);
	//printf("%d %d\n",ans1,ans2);
	//cout<<"YES"<<endl;
	ans=0;
	int nn=num;
	for (int i=2;i<=nn;i+=2)
	if (i%2==0) addflow(Fro[i],vet[i],1<<29,tim[i],1);
	S=0;
  addflow(S,1,KK,0,1);
	Mcf::work();
	printf("%d\n",ans);
	return 0;
}
