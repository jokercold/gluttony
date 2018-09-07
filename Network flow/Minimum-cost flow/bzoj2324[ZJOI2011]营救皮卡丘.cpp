#include<iostream>
#include<cstdio>
using namespace std;
#define N 400
#define M 80000
int floyd[200][200];
int n,m,KK,S,T,num,ans;
namespace Mcf{
	int dis[N],hed[N],q[N],from[N];
	bool inq[N];
	int vet[M],val[M],Fro[M],cost[M],Next[M];
	void add(int u,int v,int flow,int c){
	  ++num;
		vet[num]=v;
		val[num]=flow;
		Fro[num]=u;
		cost[num]=c;
		Next[num]=hed[u];
		hed[u]=num;
	}
  void addflow(int u,int v,int flow,int c){
		//cout<<u<<" "<<v<<" "<<flow<<" "<<c<<endl;
	  add(u,v,flow,c);
		add(v,u,0,-c);
	}
  bool spfa(){
	  int hh=0,tt=1;
		for (int i=1;i<=T;++i) dis[i]=1<<29,inq[i]=false;
		q[0]=S;inq[S]=true;dis[S]=0;
		while (hh!=tt){
		  int u=q[hh];
			inq[u]=false;
			++hh;
			if (hh==N-10) hh=0;
			for (int i=hed[u];i!=-1;i=Next[i]){
				int v=vet[i];
				if (val[i]&&dis[u]+cost[i]<dis[v]){
				  dis[v]=dis[u]+cost[i];
					//cout<<v<<" "<<dis[v]<<endl;
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
		return dis[T]!=1<<29;
	}
	void mcf(){
	  int flow=1<<29;
		for (int i=from[T];i;i=from[Fro[i]]) flow=min(flow,val[i]);
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
  scanf("%d%d%d",&n,&m,&KK);
	++n;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j) floyd[i][j]=1<<29;
  for (int i=1;i<=m;++i){
	  int a,b,l;
		scanf("%d%d%d",&a,&b,&l);
		++a;++b;
		floyd[a][b]=min(floyd[a][b],l);
		floyd[b][a]=min(floyd[b][a],l);
	}
	for (int k=1;k<=n;++k)
		for (int i=1;i<=n;++i)
		if (i!=k)
			for (int j=1;j<=n;++j) if (k!=j&&i!=j)
				if (k<i||k<j) floyd[i][j]=min(floyd[i][j],floyd[i][k]+floyd[k][j]);
	S=n+n+1;
	T=S+1;
  num=1;
	using namespace Mcf;
	for (int i=1;i<=T;++i) hed[i]=-1,from[i]=0;
}
void build(){
  using namespace Mcf;
  for (int i=2;i<=n;++i)
	  addflow(S,i,1,0),addflow(i+n,T,1,0);
	addflow(S,1,KK,0);addflow(n+1,T,1,0);
	for (int i=1;i<=n;++i)
		for (int j=i+1;j<=n;++j)
		if (floyd[i][j]!=1<<29){
			//cout<<"(((((((((((((((((("<<i<<" "<<j<<" "<<floyd[i][j]<<endl;
			addflow(i,j+n,1,floyd[i][j]);
    }
}
int main(){
  init();
	build();
	//cout<<"YES"<<endl;
	Mcf::work();
	printf("%d\n",ans);
	return 0;
}
