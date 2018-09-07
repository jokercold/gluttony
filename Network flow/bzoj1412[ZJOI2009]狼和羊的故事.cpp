#include<iostream>
#include<cstdio>
using namespace std;
#define M 80100
#define N 10010
int dx[5],dy[5];
int map[105][105];
int Next[M],val[M],vet[M];
int hed[N],q[N],cur[N],h[N];
int n,m,num,S,T,ans;
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
int calc(int i,int j){
  return (i-1)*m+j;
}
bool bfs(){
  int tt=1,hh=1;
  for (int i=1;i<=T;++i) h[i]=-1;
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
		for (int i=1;i<=T;++i) cur[i]=hed[i];
		ans+=dfs(S,1<<29);
	}
}
void init(){
	dx[0]=-1;dy[0]=0;
	dx[1]=0;dy[1]=-1;
	dx[2]=0;dy[2]=1;
	dx[3]=1;dy[3]=0;
	scanf("%d%d",&n,&m);
	S=n*m+1;
	T=n*m+2;
  for (int i=1;i<=T;++i) hed[i]=-1;
}
void build(){	
  num=1;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			scanf("%d",&map[i][j]);
			int a=calc(i,j);
	    if  (map[i][j]==1) addflow(S,a,1<<29);
			else if (map[i][j]==2) addflow(a,T,1<<29);
			if (map[i][j]==2) continue;
			for (int k=0;k<4;++k){
			  int di=i+dx[k];
				int dj=j+dy[k];
				if (di<1||di>n||dj<1||dj>m) continue;
				if (map[di][dj]!=1) addflow(a,calc(di,dj),1);
			}		
		}
}
int main(){
	init();
	build();
	dinic();
	printf("%d\n",ans);
	return 0;
}
