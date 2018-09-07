#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){
  char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
  return tmp;
}
#define N 100005
#define M 1000005
int dx[4]={0,0,1,-1};
int dy[4]={-1,1,0,0};
int f[50][50][50];
int hed[N],cur[N],h[N],st[N];
int Next[M],val[M],vet[M];
int num;
void add(int u,int v,int z){
  ++num;
	vet[num]=v;
	val[num]=z;
	Next[num]=hed[u];
	hed[u]=num;
}
void add_flow(int u,int v,int w){
  add(u,v,w);
	add(v,u,0);
}
int P,Q,R,D,S,T;
bool bfs(){
  int hh=0,tt=1;
	for (int i=1;i<=T;++i) h[i]=-1;
  st[hh]=S;h[S]=1;
	while (hh!=tt){
	  int u=st[hh];++hh;
		for (int i=hed[u];i!=-1;i=Next[i]){
		  int v=vet[i];
			if (val[i]&&h[v]==-1){
			  h[v]=h[u]+1;
				st[tt]=v;
				++tt;
			}
		}
	}
	return h[T]!=-1;
}
int dinic(int u,int low){
  if (u==T) return low;
	int used=0;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (val[i]&&h[v]==h[u]+1){
		  int w=dinic(v,min(val[i],low-used));
			val[i]-=w;
			val[i^1]+=w;
			used+=w;
			cur[u]=i;
			if (used==low) return used;
		}
	}
	if (used==0) h[u]=-1;
	return used;
}
int cal(int x,int y,int z){
  if (z==0) return S;
	return (z-1)*P*Q+(x-1)*Q+y;
}
void build(){
	num=1;
  for (int i=1;i<=P;++i)
		for (int j=1;j<=Q;++j){
			for (int k=1;k<=R;++k){
				add_flow(cal(i,j,k-1),cal(i,j,k),f[i][j][k]);
				if (k>D)
					for (int TJ=0;TJ<4;++TJ){
					  int nx=i+dx[TJ],ny=j+dy[TJ];
            if (nx<1||nx>P||ny<1||ny>Q) continue;
						add_flow(cal(i,j,k),cal(nx,ny,k-D),1<<29);
					}
			}
			add_flow(cal(i,j,R),T,1<<29);
		}
}
int main(){
  P=read();Q=read();R=read();D=read();
	S=P*Q*R+1;
	T=P*Q*R+2;
	for (int i=1;i<=T;++i) hed[i]=-1;
	for (int k=1;k<=R;++k)
		for (int i=1;i<=P;++i)
			for (int j=1;j<=Q;++j) f[i][j][k]=read();
	//cout<<"YES"<<endl;
  build();
	int ans=0;
	while (bfs()){
	  //cout<<"YES"<<endl;
		for (int i=1;i<=T;++i) cur[i]=hed[i];
		ans+=dinic(S,1<<29);
		//cout<<ans<<endl;
	}
	printf("%d\n",ans);
	return 0;
}
