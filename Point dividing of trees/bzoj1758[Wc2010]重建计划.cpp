#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define db double
#define eps 1e-4
#define fir first
#define sec second
#define N 100100
pair<int,int> A[N];
bool vis[N];
int hed[N],vet[N*2],Next[N*2],val[N*2],siz[N],dep[N],fa[N],DQ[N];
db dis[N],mx[N],Q[N];
int num,L,U,lim;
db ans;
inline void add(int u,int v,int z){
  ++num;
	vet[num]=v;
	val[num]=z;
	Next[num]=hed[u];
	hed[u]=num;
}
void get_size(int u,int fa){
	siz[u]=1;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fa||vis[v]) continue;
	  get_size(v,u);
		siz[u]+=siz[v];
	}
}
int get_root(int u,int fa,int maxsiz){
	//cout<<u<<" "<<maxsiz<<endl;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fa||vis[v]) continue;
		if (siz[v]+siz[v]>maxsiz) return get_root(v,u,maxsiz);
	}
	return u;
}
int tt;
void makeson(int u,int fa,int deep,db z,db M){
	if (tt<deep){
	  Q[deep]=-1<<29;
		tt=deep;
	}
	Q[deep]=max(Q[deep],z);
  for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fa||vis[v]) continue;
		makeson(v,u,deep+1,z+(db)val[i]-M,M);
	}
}
bool cal(int x,db M){
	//cout<<x<<endl;
	int T=0;
	for (int i=hed[x];i!=-1;i=Next[i]){
	  int v=vet[i];
		dis[v]=(db)val[i]-M;
		if (vis[v]) continue;
    ++T;
		A[T]=make_pair(siz[v],v);
	}
  sort(A+1,A+T+1);
	int MX=0;
	for (int cas=1;cas<=T;++cas){
		int VV=A[cas].sec;
		tt=0;
    makeson(VV,x,1,dis[VV],M);
		//cout<<"YES"<<endl;
		int H=1,T=0,now=MX;
		for (int i=1;i<=tt;++i){
			//cout<<x<<" "<<VV<<" "<<Q[i]<<endl;	
			while (i+now>=L&&now>=0){
			  while (H<=T&&mx[DQ[T]]<mx[now]) T--;
				DQ[++T]=now;
				now--;
			}
			while (H<=T&&i+DQ[H]>U) H++;
			/*cout<<"ha:"<<ha<<endl;
			cout<<"dis[ha]:"<<dis[ha]<<endl;
			cout<<"DQ[L]:"<<DQ[L]<<endl;
			cout<<"mx[DQ[L]]:"<<mx[DQ[L]]<<endl;*/
			if (H<=T&&Q[i]+mx[DQ[H]]>=0)return true;
		}
		//cout<<"YES"<<endl;
		for (int i=MX+1;i<=tt;++i) mx[i]=-1<<29;
		for (int i=1;i<=tt;++i)
			mx[i]=max(mx[i],Q[i]);
		MX=max(MX,tt);
	}
	return false;
}
void check(int x){
  db l=ans,r=lim;
	while (l<r-eps){
	  db mid=(l+r)/2;
		if (cal(x,mid)) l=mid;
		else r=mid;
	}
	ans=l;
}
void dfs(int x){
  vis[x]=true;
	get_size(x,0);
	check(x);
	for (int i=hed[x];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (vis[v]) continue;
		int xx=get_root(v,0,siz[v]);
		dfs(xx);
	}
}
int n;
void work(){	
	get_size(1,0);
	int xx=get_root(1,0,siz[1]);
	dfs(xx);
}
int main(){
	scanf("%d",&n);
	scanf("%d%d",&L,&U);
	num=0;
	lim=0;
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=1;i<n;++i){
	  int u,v,z;
		scanf("%d%d%d",&u,&v,&z);
		add(u,v,z);
		add(v,u,z);
		lim=max(lim,z);
	}
	ans=(db)0.0;
	work();
	printf("%.3lf\n",ans);
	return 0;
}
