#include<iostream>
#include<cstdio>
using namespace std;
int num,id;
#define N 105000
int vet[N*2],Next[N*2];
int dep[N],hed[N],IN[N],OUT[N],F[N][20];
int ch[N][2],f[N],haha[N];
int Ma[N*4],tag[N*4];
void add(int u,int v){
  ++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
void dfs(int u,int fa){
  F[u][0]=fa;
	f[u]=fa;
	dep[u]=dep[fa]+1;
	IN[u]=++id;
	haha[id]=u;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fa) continue;
		dfs(v,u);
	}
	OUT[u]=id;
}
void update(int p){
  Ma[p]=max(Ma[p<<1],Ma[p<<1|1]);
}
void pushdown(int p){
  if (tag[p]){
	  Ma[p<<1]+=tag[p];
		tag[p<<1]+=tag[p];
		Ma[p<<1|1]+=tag[p];
		tag[p<<1|1]+=tag[p];
		tag[p]=0;
	}
}
void build(int p,int l,int r){
  if (l==r){
	  Ma[p]=dep[haha[l]];
		//cout<<p<<" "<<Ma[p]<<endl;
		tag[p]=0;
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
  update(p);
}
void insert(int p,int l,int r,int x,int y,int z){
  if (l==x&&r==y){
	  Ma[p]+=z;
		tag[p]+=z;
	  return;
	}
  pushdown(p);
	int mid=(l+r)>>1;
	if (y<=mid) insert(p<<1,l,mid,x,y,z);
	else if (x>=mid+1) insert(p<<1|1,mid+1,r,x,y,z);
	else{
	  insert(p<<1,l,mid,x,mid,z);
		insert(p<<1|1,mid+1,r,mid+1,y,z);
	}
	update(p);
}
int query(int p,int l,int r,int x,int y){
	//cout<<Ma[p]<<" "<<l<<" "<<r<<endl;
  if (l==x&&r==y) return Ma[p];
  pushdown(p);
	int mid=(l+r)>>1;
	if (y<=mid) return query(p<<1,l,mid,x,y);
	if (x>=mid+1) return query(p<<1|1,mid+1,r,x,y);
	return max(query(p<<1,l,mid,x,mid),query(p<<1|1,mid+1,r,mid+1,y));
}
bool isroot(int x){
  return (ch[f[x]][1]!=x&&ch[f[x]][0]!=x);
}
void rotate(int x){
  int y=f[x],z=f[y];
	int l=(ch[y][1]==x),r=l^1;
	if (!isroot(y)) ch[z][ch[z][1]==y]=x;
	f[x]=z;f[y]=x;f[ch[x][r]]=y;
	ch[y][l]=ch[x][r];ch[x][r]=y;
}
void splay(int x){
	while (!isroot(x)){
	  int y=f[x],z=f[y];
		if (!isroot(y)){
		  if (ch[y][0]==x^ch[z][0]==y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x){
  int y=0;
	while (x){
	  splay(x);
		if (ch[x][1]){
			int xx=ch[x][1];
			while (ch[xx][0]) xx=ch[xx][0];
			insert(1,1,id,IN[xx],OUT[xx],1);
		}
		if (y){
			int xx=y;
			while (ch[xx][0]) xx=ch[xx][0];
			insert(1,1,id,IN[xx],OUT[xx],-1);
		}
		ch[x][1]=y;
		y=x;x=f[x];
	}
}
int lca(int u,int v){
  if (dep[u]<dep[v]) swap(u,v);
	for (int i=17;i>=0;--i)
	if (dep[F[u][i]]>=dep[v]) u=F[u][i];
	if (u==v) return u;
  for (int i=17;i>=0;--i)
	if (F[u][i]!=F[v][i]) u=F[u][i],v=F[v][i];
	return F[u][0];
}
int get_sum(int x){
  int ans=0;
	while (x){
		splay(x);
	  x=f[x];
		++ans;
	}
	return ans;
}
int main(){
  int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	id=0;
	dep[0]=0;
	dfs(1,0);
	for (int j=1;j<=17;++j)
		for (int i=1;i<=n;++i)
		F[i][j]=F[F[i][j-1]][j-1];
	build(1,1,id);
	while (m--){
		int opt,x;
		scanf("%d%d",&opt,&x);
		if (opt==1) access(x);
		if (opt==2){
		  int y;
			scanf("%d",&y);
			int z=lca(x,y);
			//cout<<get_sum(x)<<" "<<get_sum(y)<<" "<<get_sum(z)<<endl;
			printf("%d\n",get_sum(x)+get_sum(y)-(get_sum(z)<<1)+1);
		}
		if (opt==3){
			//cout<<IN[x]<<" "<<OUT[x]<<endl;
			printf("%d\n",query(1,1,id,IN[x],OUT[x]));
		}
	}
	return 0;
}
