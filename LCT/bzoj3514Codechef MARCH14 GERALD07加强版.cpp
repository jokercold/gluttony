#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){
  char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
  int tmp=0;
	while (ch>='0'&&ch<='9')tmp=tmp*10+ch-'0',ch=getchar();
	return tmp;
}
#define N 400050
int sz;
int ch[N][2],val[N],mn[N],rev[N],f[N],stack[N];
int U[N],V[N],ls[N*10],rs[N*10],sum[N*10],root[N],st[N];
bool isroot(int x){
  return (ch[f[x]][0]!=x&&ch[f[x]][1]!=x);
}
void update(int x){
  if (x){
		int l=ch[x][0],r=ch[x][1];
	  mn[x]=x;
		if (val[mn[l]]<val[mn[x]]) mn[x]=mn[l];
		if (val[mn[r]]<val[mn[x]]) mn[x]=mn[r];
	}
}
void pushdown(int x){
  if (x&&rev[x]){
	  swap(ch[x][0],ch[x][1]);
		rev[ch[x][0]]^=1;
		rev[ch[x][1]]^=1;
		rev[x]^=1;
	}
}
void rotate(int x){
  int y=f[x],z=f[y];
	int l=(ch[y][1]==x),r=l^1;
	if (!isroot(y)) ch[z][ch[z][1]==y]=x;
	f[x]=z;f[y]=x;f[ch[x][r]]=y;
	ch[y][l]=ch[x][r];ch[x][r]=y;
	update(y);update(x);
}
void splay(int x){
  int top=0;
	stack[++top]=x;
	for (int i=x;!isroot(i);i=f[i]) stack[++top]=f[i];
  for (int i=top;i;i--) pushdown(stack[i]);
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
		ch[x][1]=y;
		update(x);
		y=x;x=f[x];
	}
}
void reverse(int x){
  access(x);splay(x);
	rev[x]^=1;
}
void cut(int x,int y){
  reverse(x);
	access(y);
	splay(y);
	ch[y][0]=f[x]=0;
}
void link(int x,int y){
  reverse(x);
	f[x]=y;
	splay(x);
}
int find(int x){
	access(x);
	splay(x);
	int y=x;
	while (ch[y][0]) y=ch[y][0];
	return y;
}
int makemin(int x,int y){
  reverse(x);
	access(y);
	splay(y);
	return mn[y];
}
void insert(int x,int &y,int l,int r,int z){
  y=++sz;
	sum[y]=sum[x]+1;
	if (l==r) return;
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if (mid>=z) insert(ls[x],ls[y],l,mid,z);
	else insert(rs[x],rs[y],mid+1,r,z);
}
int query(int x,int y,int l,int r,int z){
  if (r==z) return sum[y]-sum[x];
	int mid=(l+r)>>1;
	if (z<=mid) return query(ls[x],ls[y],l,mid,z);
	else return sum[ls[y]]-sum[ls[x]]+query(rs[x],rs[y],mid+1,r,z);
}
int main(){
	sz=0;
  int n,m,K,type;
	scanf("%d%d%d%d",&n,&m,&K,&type);
	for (int i=1;i<=m;++i) U[i]=read(),V[i]=read();
	//cout<<"YES"<<endl;
	for (int i=0;i<=n;++i) mn[i]=i,val[i]=1<<29;
	int tot=n;
	for (int i=1;i<=m;++i){
	  if (U[i]==V[i]){
			st[i]=i;
		  continue;
		}
		if (find(U[i])==find(V[i])){
		  int x=makemin(U[i],V[i]);
			st[i]=val[x];
      cut(U[val[x]],x);cut(V[val[x]],x);
		}
		++tot;
		mn[tot]=tot;val[tot]=i;
		link(U[i],tot);link(V[i],tot);
	}
	for (int i=1;i<=m;++i)
		insert(root[i-1],root[i],0,m,st[i]);
	int ans=0;
	while (K--){
	  int l,r;
		scanf("%d%d",&l,&r);
    if (type) l^=ans,r^=ans;
		ans=n-query(root[l-1],root[r],0,m,l-1);
		printf("%d\n",ans);
	}
	return 0;
}

