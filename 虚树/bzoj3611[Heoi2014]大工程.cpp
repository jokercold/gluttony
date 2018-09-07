#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
int cnt,num,K,Cas,n;
ll ans;
int mn,mx;
#define N 1005000
#define M 2005000
int vet[M],val[M],Next[M];
int hed[N],dfsn[N],dep[N];
ll siz[N];
int st[N];
int mnf[N],mxf[N];
int h[N],v[N];
int fa[N][21];
inline int read(){
  char last='+',ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') last='-';ch=getchar();}
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+(ch-'0');ch=getchar();};
  if (last=='-') tmp=-tmp;
	return tmp;
}
void add(int u,int v){
  if (u==v) return;
	++num;
	vet[num]=v;
	val[num]=dep[v]-dep[u];
  //cout<<u<<" "<<v<<" "<<val[num]<<endl;
	Next[num]=hed[u];
	hed[u]=num;
}
bool cmp(int x,int y){
  return dfsn[x]<dfsn[y];
}
void dfs(int u,int fath){
  dfsn[u]=++cnt;
	fa[u][0]=fath;
	dep[u]=dep[fath]+1;
  for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fath) continue;
		dfs(v,u);
	}
}
void pre(){
  for (int j=1;j<=20;++j)
		for (int i=1;i<=n;++i)
		fa[i][j]=fa[fa[i][j-1]][j-1];
}
int lca(int u,int v){
  if (dep[u]<dep[v]) std::swap(u,v);
	for (int i=20;i>=0;--i)
	if (dep[u]-(1<<i)>=dep[v]) u=fa[u][i];
	if (u==v) return u;
	for (int i=20;i>=0;--i)
	if (fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
void dp(int u){
  siz[u]=(v[u]==Cas)?1:0;
	mnf[u]=(v[u]==Cas)?0:1<<29;
	mxf[u]=(v[u]==Cas)?0:-1<<29;
	for (int i=hed[u];i!=-1;i=Next[i]){
		int v=vet[i];
		//cout<<u<<" "<<v<<endl;
		dp(v);
		siz[u]+=siz[v];
		ans+=(ll)siz[v]*val[i]*(K-siz[v]);
		//cout<<mnf[u]<<" "<<v<<"----->"<<mnf[v]<<endl;
		mn=std::min(mn,mnf[u]+mnf[v]+val[i]);
		mx=std::max(mx,mxf[u]+mxf[v]+val[i]);
		mnf[u]=std::min(mnf[u],mnf[v]+val[i]);
		mxf[u]=std::max(mxf[u],mxf[v]+val[i]);
	}
	//cout<<u<<":"<<" "<<siz[u]<<endl;
	//cout<<u<<" "<<mnf[u]<<" "<<mxf[u]<<endl;
	hed[u]=-1;
}
void solve(){
  K=read();
	for (int i=1;i<=K;++i) h[i]=read(),v[h[i]]=Cas;
	//cout<<h[1]<<" "<<h[2]<<endl;
	//cout<<K<<endl;
	std::sort(h+1,h+K+1,cmp); 
	num=0;
	int top=0;
	st[++top]=1;
	for(int i=1;i<=K;i++){
		int x=h[i],f=lca(x,st[top]);
		if(f==st[top]){st[++top]=x;continue;}
		while(f==lca(x,st[top-1])){
			add(st[top-1],st[top]);
			top--;f=lca(x,st[top]);
		}
		add(f,st[top]);
		st[top]=f;st[++top]=x;
	}
	while(--top) add(st[top],st[top+1]);	
	ans=0;
	mn=1<<29;
	mx=-1<<29;
	//cout<<"YES"<<endl;
	dp(1);
  printf("%lld %d %d\n",ans,mn,mx);
}
int main(){
	cnt=0;num=0;
	n=read();
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=1;i<n;++i){
	  int u,v;
		u=read();v=read();
		//cout<<u<<" "<<v<<endl;
		add(u,v);
		add(v,u);
	}
	dep[0]=0;
	dfs(1,0);
	pre();
	for (int i=1;i<=n;++i) hed[i]=-1;
	int q;
	q=read();
  for (int i=1;i<=q;++i){
		Cas=i;
		solve();
	}
	return 0;
}
