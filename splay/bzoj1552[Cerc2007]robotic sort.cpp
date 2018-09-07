#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 200000
int root;
struct node{
  int v,id;
}h[N];
bool cmp1(node x,node y){
  if (x.v!=y.v) return x.v<y.v;
	else return x.id<y.id;
}
bool cmp2(node x,node y){
  return x.id<y.id;
}
namespace Splay{
	int ch[N][2],siz[N],mn[N],id[N],f[N],rev[N],st[N],v[N];
	void update(int x){
	  int l=ch[x][0],r=ch[x][1];
		siz[x]=1;
		if (l) siz[x]+=siz[l];
		if (r) siz[x]+=siz[r];
    mn[x]=v[x];id[x]=x;
    if (l&&mn[x]>mn[l]){mn[x]=mn[l];id[x]=id[l];}
		if (r&&mn[x]>mn[r]){mn[x]=mn[r];id[x]=id[r];}
	}
	void pushdown(int x){
	  if (rev[x]){
		  swap(ch[x][0],ch[x][1]);
			rev[ch[x][0]]^=1;rev[ch[x][1]]^=1;
			rev[x]^=1;
		}
	}
	void rotate(int x,int &k){
	  int y=f[x],z=f[y];
		int l=(ch[y][1]==x),r=l^1;
		if (y==k) k=x;
		else ch[z][ch[z][1]==y]=x;
		f[x]=z;f[y]=x;f[ch[x][r]]=y;
    ch[y][l]=ch[x][r];ch[x][r]=y;
		update(y);update(x);
	}
  void splay(int x,int &k){
	  //cout<<x<<" "<<f[x]<<" "<<f[f[x]]<<endl;
		int top=0;
		st[++top]=x;
		for (int i=x;f[i];i=f[i]) 
			st[++top]=f[i];
    for (int i=top;i;i--)
			pushdown(st[i]);
		while (x!=k){
		  int y=f[x],z=f[y];
			//cout<<x<<" "<<y<<" "<<z<<endl;
		  if (y!=k){
			  if (ch[y][0]==x^ch[z][0]==y) rotate(x,k);
				else rotate(y,k);
			}
			//cout<<x<<" "<<y<<" "<<z<<endl;
			rotate(x,k);
		}
		//cout<<"YES"<<endl;
	}
	int find(int x){
	  int now=root;
		while (now){
			pushdown(now);
			if (ch[now][0]&&x<=siz[ch[now][0]]) now=ch[now][0];
			else{
			  int temp=(ch[now][0]?siz[ch[now][0]]:0)+1;
				if (x<=temp) return now;
				x-=temp;
				now=ch[now][1];
			}
		}
	}
	int querymn(int l,int r){
		//cout<<root<<endl;
	  int x=find(l),y=find(r+2);
    //cout<<x<<" "<<y<<endl;
		splay(x,root);splay(y,ch[x][1]);
    int z=ch[y][0];
		//cout<<mn[z]<<" "<<id[z]<<endl;
		return id[z];
	}
	void rever(int l,int r){
	  int x=find(l),y=find(r+2);
		splay(x,root);splay(y,ch[x][1]);
		int z=ch[y][0];
		rev[z]^=1;
	}
	void build(int l,int r,int fa){
	  if (l>r) return;
		int mid=(l+r)>>1,now=mid,last=fa;
    if (l==r){
			mn[l]=h[l].v;
      id[l]=l;
			siz[l]=1;
		}else build(l,mid-1,mid),build(mid+1,r,mid);
	  f[now]=last;
		v[now]=h[mid].v;
		update(now);
    ch[last][mid>=fa]=now;
	}
} 
int main(){
	int n;
	scanf("%d",&n);
	for (int i=2;i<=n+1;++i) scanf("%d",&h[i].v),h[i].id=i;
  sort(h+2,h+n+2,cmp1);
	for (int i=2;i<=n+1;++i) h[i].v=i-1;
	sort(h+2,h+n+2,cmp2);
	h[1].id=1;h[n+2].id=n+2;
	h[1].v=1<<29;h[n+2].v=1<<29;
	using namespace Splay;
	build(1,n+2,0);
  root=(n+3)>>1;
	for (int i=1;i<=n;++i){
		//cout<<"______________"<<i<<"___________"<<endl;
	  int pos=querymn(i,n);
		splay(pos,root);
		//cout<<siz[ch[pos][0]]<<" "<<" "<<siz[ch[pos][1]]<<endl;
		printf("%d%c",siz[ch[pos][0]]," \n"[i==n]);
		rever(i,siz[ch[pos][0]]);
	}
	return 0;
}
