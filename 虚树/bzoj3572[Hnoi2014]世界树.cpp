#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
#define N 350000
#define M 650000
int vet[M],Next[M],hed[N];
int dep[N],fa[N][22],siz[N],rest[N],member[N],ans[N],bel[N],st[N],h[N],dfsn[N],id[N];
int cnt,num,n;
void add(int u,int v){
  if (u==v) return;
	++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
void dfs(int u,int fath){
	dfsn[u]=++cnt;
  fa[u][0]=fath;
	dep[u]=dep[fath]+1;
	siz[u]=1;
  for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fath) continue;
		dfs(v,u);
	  siz[u]+=siz[v];
	}
}
void pre(){
  for (int j=1;j<=18;++j)
		for (int i=1;i<=n;++i) 
		fa[i][j]=fa[fa[i][j-1]][j-1];
}
int lca(int u,int v){
  if (dep[u]<dep[v]) swap(u,v);
	for (int i=18;i>=0;--i)
	if (dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if (u==v) return u;
	for (int i=18;i>=0;--i)
	if (fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int dis(int u,int v){
	return dep[u]+dep[v]-dep[lca(u,v)]*2;
}
void dfs1(int u){
  rest[u]=siz[u];
	//cout<<cnt<<" "<<u<<endl;
  member[++cnt]=u;
	//cout<<u<<" "<<fath<<endl;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		dfs1(v); 
		if (bel[v]==0) continue;
		if (bel[u]==0){bel[u]=bel[v];continue;}
		int down=dis(bel[v],u),up=dis(bel[u],u);
		if (down<up||(down==up&&bel[v]<bel[u])) bel[u]=bel[v];
	}
}
void dfs2(int u){
	for (int i=hed[u];i;i=Next[i]){
	  int v=vet[i];
		int down=dis(bel[v],v),up=dis(bel[u],v);
    if (down>up||(down==up&&bel[v]>bel[u])||!bel[v]) bel[v]=bel[u];
		dfs2(v);
	}
}
void solve(int fath,int u){
  int son=u;
	for (int i=18;i>=0;--i)
	if (dep[fa[son][i]]>dep[fath]) son=fa[son][i];
	//cout<<fath<<" "<<u<<" "<<son<<endl;
	//cout<<rest[fath]<<" "<<siz[son]<<endl;
	rest[fath]-=siz[son];
	//cout<<rest[fath]<<endl;
	//cout<<u<<" "<<fath<<" "<<ans[bel[3]]<<endl;
	if (bel[fath]==bel[u]){ans[bel[fath]]+=siz[son]-siz[u];return;}
	int mid=u;
	//cout<<"YES"<<endl;
	for (int i=18;i>=0;--i){
	  int nex=fa[mid][i];
		if (dep[nex]<=dep[fath]) continue;
		int down=dis(bel[u],nex),up=dis(bel[fath],nex);
    if (down<up||(down==up&&bel[u]<bel[fath])) mid=nex;
	}
	ans[bel[fath]]+=siz[son]-siz[mid];
	ans[bel[u]]+=siz[mid]-siz[u];
	/*cout<<u<<"________________>"<<siz[u]<<endl;
	cout<<fath<<"_______________>"<<siz[fath]<<endl;
	cout<<mid<<"_____________>"<<siz[mid]<<endl;
	cout<<endl;*/
	//cout<<u<<" "<<fath<<"------"<<mid<<endl;
	//cout<<siz[fath]<<" "<<siz[son]<<" "<<siz[u]<<endl;
}
bool cmp(int x,int y){
  return dfsn[x]<dfsn[y];
}
void build(){
	cnt=0;
  int m;
	scanf("%d",&m);
	for (int i=1;i<=m;++i) scanf("%d",&h[i]),bel[h[i]]=h[i],id[i]=h[i];
	//cout<<bel[6]<<endl;
	sort(h+1,h+m+1,cmp);
	int top=0;
  num=0;
	//cout<<"YES"<<endl;
	if(bel[1]!=1) st[++top]=1;
	for (int i=1;i<=m;++i){
		//cout<<i<<endl;
		if (!top){st[++top]=h[i];continue;}
		//cout<<i<<endl;
		int now=h[i],f=lca(now,st[top]);
		if (f==st[top]){st[++top]=now;continue;}
		//cout<<now<<" "<<st[top]<<" "<<f<<endl;
		while (f==lca(h[i],st[top-1])){
		  add(st[top-1],st[top]);
	    top--;f=lca(now,st[top]);
			//cout<<f<<endl;
		}
		add(f,st[top]);
		st[top]=f;st[++top]=now;
	}
	//cout<<top<<endl;
	while (--top) add(st[top],st[top+1]);
  //cout<<top<<endl;
	//cout<<bel[6]<<endl;
	dfs1(1);
	dfs2(1);
	//cout<<cnt<<endl;
	//for (int i=1;i<=cnt;++i) printf("%d%c",member[i]," \n"[i==cnt]);
	//cout<<bel[6]<<endl;
	for (int i=1;i<=cnt;++i)
		for (int j=hed[member[i]];j!=-1;j=Next[j])
			solve(member[i],vet[j]);
	//cout<<"YES"<<endl;
	//cout<<bel[6]<<endl;
	for (int i=1;i<=cnt;++i) ans[bel[member[i]]]+=rest[member[i]];
	for (int i=1;i<=m;++i) printf("%d ",ans[id[i]]);
	printf("\n");
	for (int i=1;i<=cnt;++i){
	  int u=member[i];
		rest[u]=ans[u]=bel[u]=0;
	  hed[u]=-1;
	}
}
int main(){
	scanf("%d",&n);
	num=0;
	cnt=0;
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=1;i<n;++i){
	  int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	pre();
	for (int i=1;i<=n;++i) hed[i]=-1;
	int q;
	scanf("%d",&q);
	while (q--) build();
	return 0;
}
