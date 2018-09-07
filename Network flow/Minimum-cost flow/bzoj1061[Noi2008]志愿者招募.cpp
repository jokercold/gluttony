#include<iostream>
#include<cstdio>
using namespace std;
#define N 2000
#define M 60000
inline int read(){
  char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	return tmp;
}
bool inq[N];
int hed[N],dis[N],q[N],from[N];
int vet[M],val[M],cost[M],Next[M],Fro[M];
int S,T,num;
void add(int u,int v,int w,int c){
  ++num;
	vet[num]=v;
	Fro[num]=u;
	val[num]=w;
	cost[num]=c;
	Next[num]=hed[u];
	hed[u]=num;
}
void addflow(int u,int v,int w,int c){
  add(u,v,w,c);
	add(v,u,0,-c);
}
bool spfa(){
  for (int i=1;i<=T;++i) dis[i]=1<<29;
	int hh=0,tt=1;
	q[hh]=S;
	dis[S]=0;
	while (hh!=tt){
	  int u=q[hh];
		inq[u]=false;
		++hh;
	  if (hh==N-10) hh=0;
		for (int i=hed[u];i!=-1;i=Next[i]){
		  int v=vet[i];
			if (val[i]&&dis[v]>dis[u]+cost[i]){
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
int main(){
  int n,m;
	//scanf("%d%d",&n,&m);
	n=read();m=read();
	S=n+2;T=n+3;
	num=1;
	int last=0;
	for (int i=1;i<=T;++i) hed[i]=-1;
	for (int i=1;i<=n+1;++i){
	  int a;
		if (i<=n) a=read();
		else a=0;
		int xx=a-last;
		last=a;
		if (xx>0) addflow(i,T,xx,0);
		if (xx<0) addflow(S,i,-xx,0);
		if (i<n+1) addflow(i,i+1,1<<29,0);
  }
	for (int i=1;i<=m;++i){
	  int s,t,c;
		s=read();t=read();c=read();
		addflow(t+1,s,1<<29,c);
	}
	int ans=0;
	while (spfa()){
		int flow=1<<29;
	  for (int i=from[T];i;i=from[Fro[i]]) flow=min(flow,val[i]);
		//cout<<flow<<endl;
		for (int i=from[T];i;i=from[Fro[i]]){
			//cout<<i<<"!"<<i<<" "<<cost[i]<<endl;
			ans+=flow*cost[i];
			val[i]-=flow;
			val[i^1]+=flow;
		}
	}
	printf("%d\n",ans);
	return 0;
}
