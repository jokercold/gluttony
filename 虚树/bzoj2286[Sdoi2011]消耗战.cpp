#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 300000
#define M 600000
#define ll long long
int hed[N],vet[M],Next[M],val[M];
int h[N],dep[N],fa[N][20],dfsn[N],st[N];
ll mn[N],f[N];
int cnt,num,n;
inline int read(){
  int x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
  return x*f;
}
void add(int u,int v,int w){
  if (u==v) return;
  ++num;
  vet[num]=v;
  val[num]=w;
  Next[num]=hed[u];
  hed[u]=num;
}
bool cmp(int x,int y){
  return dfsn[x]<dfsn[y];
}
void dfs(int x,int fath){
  dfsn[x]=++cnt;
  dep[x]=dep[fath]+1;
  fa[x][0]=fath;
  for (int i=hed[x];i!=-1;i=Next[i]){
    int v=vet[i];
    if (v==fath) continue;
    mn[v]=min(mn[x],(ll)val[i]);
    dfs(v,x);
  }
}
void pre(){
  for (int j=1;j<=18;++j)
    for (int i=1;i<=n;++i)
    fa[i][j]=fa[fa[i][j-1]][j-1];
}
int lca(int x,int y){
  if (dep[x]<dep[y]) swap(x,y);
  for (int i=18;i>=0;--i)
  if (dep[fa[x][i]]>=dep[y]) x=fa[x][i];
  if (x==y) return x;
  for (int i=18;i>=0;--i)
  if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
  return fa[x][0];
}
void dp(int x){
	//cout<<x<<endl;
  f[x]=mn[x];
  ll tmp=0;
  for (int i=hed[x];i!=-1;i=Next[i]){
    int v=vet[i];
		//cout<<x<<" "<<v<<endl;
    dp(v);
    tmp+=f[v];
  }
  hed[x]=-1;
  if (tmp==0) f[x]=mn[x];
  else f[x]=min(f[x],tmp);
}
void solve(){
  int K=read();
  for (int i=1;i<=K;++i) h[i]=read();
  sort(h+1,h+K+1,cmp);
	int tot=0;
	h[++tot]=h[1];
	for (int i=2;i<=K;++i)
	if (lca(h[tot],h[i])!=h[tot]) h[++tot]=h[i];
  num=0;
	int top=0;
	st[++top]=1;
	for(int i=1;i<=tot;i++){
		int x=h[i],f=lca(x,st[top]);
		if(f==st[top]){st[++top]=x;continue;}
		while(f==lca(x,st[top-1])){
			add(st[top-1],st[top],0);
			top--;f=lca(x,st[top]);
		}
		add(f,st[top],0);
		st[top]=f;st[++top]=x;
	}
	while(--top) add(st[top],st[top+1],0);	
  dp(1);
  printf("%lld\n",f[1]);  
}
int main(){
  n=read();
  num=0;
  for (int i=1;i<=n;++i) hed[i]=-1;
  for (int i=1;i<n;++i){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    add(u,v,w);
    add(v,u,w);
  }
  mn[1]=1ll<<60;
  dep[0]=0;
  dfs(1,0);
  pre();
	for (int i=1;i<=n;++i) hed[i]=-1;
  int m=read();
  for (int i=1;i<=m;++i)
    solve();
  return 0;
}
