#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 200000
struct node{
  int x,y,a,b;
}Q[N];
int mn[N],val[N],f[N],st[N],ch[N][2],rev[N];
bool cmp(node x,node y){
  return x.a<y.a;
}
void update(int x){
  int l=ch[x][0],r=ch[x][1];
	mn[x]=x;
	if (val[mn[l]]>val[mn[x]]) mn[x]=mn[l];
	if (val[mn[r]]>val[mn[x]]) mn[x]=mn[r];
}
void pushdown(int x){
  if (x&&rev[x]){
	  swap(ch[x][0],ch[x][1]);
		rev[ch[x][0]]^=1;
		rev[ch[x][1]]^=1;
		rev[x]^=1;
	}
}
bool isroot(int x){
  return (ch[f[x]][0]!=x&&ch[f[x]][1]!=x);
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
	st[++top]=x;
	for (int i=x;!isroot(i);i=f[i]) st[++top]=f[i];
	for (;top;top--) pushdown(st[top]);
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
  access(x);splay(x);rev[x]^=1;
}
void link(int x,int y){
  reverse(x);
	f[x]=y;
	splay(x);
}
void cut(int x,int y){
  reverse(x);
  access(y);
	splay(y);
	ch[y][0]=f[x]=0;
	update(y);
}
int query(int x,int y){
  reverse(x);
	access(y);
	splay(y);
	return mn[y];
}
int find(int x){
	access(x);
	splay(x);
	int y=x;
	while (ch[y][0]) y=ch[y][0];
	return y;
}
int main(){
  int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i) scanf("%d%d%d%d",&Q[i].x,&Q[i].y,&Q[i].a,&Q[i].b);
	sort(Q+1,Q+m+1,cmp);
	int ans=1<<29;
	int tot=n;
	for (int i=0;i<=n;++i) mn[i]=i,val[i]=0;
	for (int i=1;i<=m;++i){
		int u=Q[i].x,v=Q[i].y;
		++tot;
		mn[tot]=tot;
		val[tot]=Q[i].b;
		if (find(u)==find(v)){
		  int x=query(u,v);
		 	if (val[x]>val[tot]){
				cut(Q[x-n].x,x);
			  cut(Q[x-n].y,x);
			  link(u,tot);
				link(v,tot);
			}
		}else link(u,tot),link(v,tot);
		if (find(1)==find(n)){
		  int x=query(1,n);
			ans=min(ans,Q[i].a+val[x]);
		}
	}
	if (ans==(1<<29)) ans=-1;
	printf("%d\n",ans);
	return 0;
}
