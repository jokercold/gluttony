#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define db double
#define N 3500
int vet[N*10],val[N*10],cost[N*10],Next[N*10];
int hed[N];
db dis[N];
int A[60][60],B[60][60],id[60][60];
int n,m,num;
void add(int u,int v,int x,int y){
  ++num;
	vet[num]=v;
	val[num]=x;
	cost[num]=y;
	Next[num]=hed[u];
	hed[u]=num;
}
bool check(db yh){
  memset(dis,0,sizeof(dis));
	for (int k=1;k<=(n+1)*(m+1);++k){
	  bool flag=false;
		for (int u=1;u<=(n+1)*(m+1);++u){
		  for (int i=hed[u];i;i=Next[i]){
			  int v=vet[i];
				if (dis[v]>dis[u]+yh*cost[i]-val[i])
					dis[v]=dis[u]+yh*cost[i]-val[i],flag=true;
			}
		}
		if (!flag) return 0;
	}
	return 1;
}
int main(){
  scanf("%d%d",&n,&m);
	int k=0;
	for (int i=0;i<=n;++i)
		for (int j=0;j<=m;++j) id[i][j]=++k;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
		  int x;
			scanf("%d",&x);
			A[i][j]=A[i][j-1]+x;
			B[i][j]=B[i-1][j]+x;
		}
	for (int i=0;i<=n;++i)
		for (int j=1;j<=m;++j){
		  int x;
			scanf("%d",&x);
			add(id[i][j-1],id[i][j],(B[i][j]<<1)-B[n][j],x);
			add(id[i][j],id[i][j-1],B[n][j]-(B[i][j]<<1),x);
		}
	for (int i=1;i<=n;++i)
		for (int j=0;j<=m;++j){
		  int x;
			scanf("%d",&x);
			add(id[i-1][j],id[i][j],A[i][m]-(A[i][j]<<1),x);
			add(id[i][j],id[i-1][j],(A[i][j]<<1)-A[i][m],x);
		}
	db l=0,r=400;
	while (r-l>1e-5){
		db mid=(l+r)/2;
		if (check(mid)) l=mid;
		else r=mid;
	}
	printf("%.3lf\n",l/4);
	return 0;
}
