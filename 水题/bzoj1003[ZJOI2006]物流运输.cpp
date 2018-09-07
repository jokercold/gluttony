#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
bool tim[105][105];
ll cost[105][105],f[105];
int dis[105],hed[105];
int vet[10050],val[10050],Next[10050],st[10050];
bool inq[105],flag[105];
int n,m,num;
void add(int u,int v,int z){
  ++num;
	vet[num]=v;
	val[num]=z;
	Next[num]=hed[u];
	hed[u]=num;
}
int spfa(int l,int r){
  for (int i=1;i<=m;++i){
	  bool ff=true;
		for (int j=l;j<=r;++j)
		if (tim[i][j]==true){ 
			ff=false;
		  break;
		}
		flag[i]=ff;
	}
  for (int i=1;i<=m;++i) dis[i]=1<<29,inq[i]=false;
	int h=0,t=1;
	st[h]=1;
	dis[1]=0;
	while (h!=t){
	  int u=st[h];
		inq[u]=false;
		++h;
		for (int i=hed[u];i!=-1;i=Next[i]){
		  int v=vet[i];
			if (flag[v]&&dis[v]>dis[u]+val[i]){
			  dis[v]=dis[u]+val[i];
				if (inq[v]==false){
				  inq[v]=true;
				  st[t]=v;
					++t;
				}
			}
		}
	}
	return dis[m];
}
int main(){
  int K,e;
	scanf("%d%d%d%d",&n,&m,&K,&e);
	for (int i=1;i<=m;++i) hed[i]=-1;
	num=0;
	for (int i=1;i<=e;++i){
		int u,v,z;
		scanf("%d%d%d",&u,&v,&z);
		add(u,v,z);
		add(v,u,z);
	}
	int Q;
	scanf("%d",&Q);
	while (Q--){
	  int P,a,b;
		scanf("%d%d%d",&P,&a,&b);
		for (int i=a;i<=b;++i)
			tim[P][i]=true;
	}
	for (int i=1;i<=n;++i)
		for (int j=i;j<=n;++j)
			cost[i][j]=spfa(i,j);
	for (int i=1;i<=n;++i) f[i]=1ll<<60;
	f[0]=0;
	for (int i=1;i<=n;++i)
		for (int j=0;j<i;++j)
		f[i]=min(f[i],f[j]+cost[j+1][i]*(i-j)+K);
	printf("%lld\n",f[n]-K);
	return 0;
}
