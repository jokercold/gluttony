#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
inline int read(){
  char last='+',ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') last='-';ch=getchar();}
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	if (last=='-') tmp=-tmp;
	return tmp;
}
char ss[50];
#define N 100500
int num,cnt,n;
struct node{
  ll minx,a,b;
}t[N*4];
bool visit[N];
int id[N],f[N][20],dep[N],siz[N],son[N],hed[N],top[N];
ll dis[N],idtt[N];
int Next[N*2],vet[N*2],val[N*2];
void build(int p,int l,int r){
  t[p].a=0;t[p].b=t[p].minx=123456789123456789;
	if (l==r) return;
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
void add(int u,int v,int w){
  ++num;
	vet[num]=v;
	val[num]=w;
	Next[num]=hed[u];
	hed[u]=num;
}
void dfs1(int u,int fa){
  visit[u]=true;
  f[u][0]=fa;
	dep[u]=dep[fa]+1;
	siz[u]=1;
	son[u]=0;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
	  if (visit[v]) continue;
		dis[v]=dis[u]+val[i];
		dfs1(v,u);
		siz[u]+=siz[v];
		if (siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int ancestor){
  visit[u]=true;
	id[u]=++cnt;idtt[cnt]=dis[u];
	top[u]=ancestor;
	if (son[u]) dfs2(son[u],ancestor);
	for (int i=hed[u];i!=-1;i=Next[i])
	if (!visit[vet[i]]) dfs2(vet[i],vet[i]);
}
int lca(int u,int v){
  if (dep[u]<dep[v]) swap(u,v);
  for (int i=17;i>=0;--i)
	if (dep[f[u][i]]>=dep[v]) u=f[u][i];
	if (u==v) return u;
	for (int i=17;i>=0;--i)
	if (f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
ll cal(ll x,ll a,ll b){
  return a*x+b;
}

void change(int p,int l,int r,ll a,ll b){
  int mid=(l+r)>>1;
	int fl=(cal(idtt[l],t[p].a,t[p].b)>cal(idtt[l],a,b));
 	int fr=(cal(idtt[r],t[p].a,t[p].b)>cal(idtt[r],a,b));
	int fm=(cal(idtt[mid],t[p].a,t[p].b)>cal(idtt[mid],a,b));
	//cout<<fl<<" "<<fm<<" "<<fr<<endl;
	if (fl&&fr&&fm){
	  t[p].a=a;
		t[p].b=b;
		t[p].minx=min(t[p].minx,min(cal(idtt[l],a,b),cal(idtt[r],a,b)));
		//cout<<t[p].maxx<<endl;
		return;
	}
	if (!(fl|fr|fm)) return;
	if (fm){
	  if (fr) change(p<<1,l,mid,t[p].a,t[p].b);
		else change(p<<1|1,mid+1,r,t[p].a,t[p].b);
		t[p].a=a;
		t[p].b=b;
		t[p].minx=min(t[p].minx,min(cal(idtt[l],a,b),cal(idtt[r],a,b)));
	}
	if (!fm){
	  if (!fr) change(p<<1,l,mid,a,b);
		else change(p<<1|1,mid+1,r,a,b);
	}
	t[p].minx=min(t[p].minx,min(t[p<<1].minx,t[p<<1|1].minx));
}
void find(int p,int l,int r,int x,int y,ll a,ll b){
  if (l==x&&r==y){
	  change(p,l,r,a,b);
		return;
	}
	int mid=(l+r)>>1;
	if (y<=mid) find(p<<1,l,mid,x,y,a,b);
	else if (x>mid) find(p<<1|1,mid+1,r,x,y,a,b);
	else{
	  find(p<<1,l,mid,x,mid,a,b);
		find(p<<1|1,mid+1,r,mid+1,y,a,b);
	}
  t[p].minx=min(t[p].minx,min(t[p<<1].minx,t[p<<1|1].minx));
}
void Change(int tt,int x,ll a,ll b){
  while (top[tt]!=top[x]){
	  find(1,1,n,id[top[x]],id[x],a,b);
		x=f[top[x]][0];
	}
	find(1,1,n,id[tt],id[x],a,b);
}
ll query(int p,int l,int r,int x,int y){
	//cout<<idtt[x]<<" "<<idtt[y]<<endl;
  ll ans=min(cal(idtt[x],t[p].a,t[p].b),cal(idtt[y],t[p].a,t[p].b));
	if (l==x&&r==y) return min(ans,t[p].minx);
	int mid=(l+r)>>1;
	if (y<=mid) return min(ans,query(p<<1,l,mid,x,y));
	if (x>mid) return min(ans,query(p<<1|1,mid+1,r,x,y));
	return min(ans,min(query(p<<1,l,mid,x,mid),query(p<<1|1,mid+1,r,mid+1,y)));
}
void Query(int u,int v){
  ll ans=123456789123456789;
	while (top[u]!=top[v]){
	  if (dep[top[u]]<dep[top[v]]) swap(u,v);
		ans=min(ans,query(1,1,n,id[top[u]],id[u]));
		u=f[top[u]][0];
	}
	if (dep[u]>dep[v]) swap(u,v);
	ans=min(ans,query(1,1,n,id[u],id[v]));
	printf("%lld\n",ans);
}
int main(){
  int m;
	n=read();m=read();
	for (int i=1;i<=n;++i) hed[i]=-1;
	num=0;
  for (int i=1;i<n;++i){
	  int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	for (int i=1;i<=n;++i) visit[i]=false;
	dfs1(1,0);
	for (int i=1;i<=n;++i) visit[i]=false;
	dfs2(1,1);
	for (int j=1;j<=17;++j)
		for (int i=1;i<=n;++i)
		f[i][j]=f[f[i][j-1]][j-1];
	build(1,1,n);
	while (m--){
	  int type;
		scanf("%d",&type);
		if (type==1){
		  int s,t;
			ll a,b;
			scanf("%d%d%lld%lld",&s,&t,&a,&b);
			int lc=lca(s,t);
			//cout<<lc<<endl;
			Change(lc,s,-a,dis[s]*a+b);
			Change(lc,t,a,(dis[s]-dis[lc]-dis[lc])*a+b);
		}else{
      int s,t;
			scanf("%d%d",&s,&t);
			Query(s,t);
		}
	}
	return 0;
}
