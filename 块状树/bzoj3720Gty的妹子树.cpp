#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxb=251;
const int maxn=100000+10;
struct Blocks{
	int a[maxb],size;
	void ins(int x){
		++size; int pos=size;
		for (int i=size;i>1&&a[i-1]>x;i--)
		    a[i]=a[i-1],pos=i-1;
		a[pos]=x;
	}
	void modify(int x,int y){
		int pos=lower_bound(a+1,a+size+1,x)-a;
		for (;pos<size&&a[pos+1]<y;++pos) a[pos]=a[pos+1];
		for (;pos>1&&a[pos-1]>y;--pos) a[pos]=a[pos-1];
		a[pos]=y;
	}
	int query(int x){
		int pos=upper_bound(a+1,a+size+1,x)-a;
		return size-pos+1;
	}
}b[10000];
int n,a[maxn],ans=0,blo,num=0;
int tot=0,cnt=0,h[maxn],kh[maxn];
struct edges{
	int to,next;
}G[maxn*2],k[maxn*2];
int belong[maxn],fa[maxn];
void getk(int x,int y){
	ans+=b[x].query(y);
	for (int i=kh[x];i;i=k[i].next)
	    getk(k[i].to,y);
}
void getans(int x,int y){
	if (a[x]>y) ++ans;
	for (int i=h[x];i;i=G[i].next){
		int v=G[i].to;
		if (v==fa[x]) continue;
	    if (belong[v]==belong[x]) getans(v,y);
	    else getk(belong[v],y);
	}
}
void add(int x,int y){
	G[++tot].to=y; G[tot].next=h[x]; h[x]=tot;
}
void Badd(int x,int y){
	k[++num].to=y; k[num].next=kh[x]; kh[x]=num;
}
void dfs(int x){
	if (b[belong[fa[x]]].size==blo)
		belong[x]=++cnt,b[cnt].ins(a[x]),Badd(belong[fa[x]],cnt);
	else b[belong[x]=belong[fa[x]]].ins(a[x]);
	for (int i=h[x];i;i=G[i].next)
	    if (G[i].to!=fa[x])
	        fa[G[i].to]=x,dfs(G[i].to);
}
int main(){
	scanf("%d",&n); blo=(int)sqrt(n);
	for (int i=1;i<n;++i){
		int x,y; scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	dfs(1); int m; scanf("%d",&m);
	for (int i=1;i<=m;++i){
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		x^=ans; y^=ans;
		if (opt==0){
			ans=0; getans(x,y);
			printf("%d\n",ans);
		}else if (opt==1){
			b[belong[x]].modify(a[x],y);
			a[x]=y;
		}else if (opt==2){
			a[++n]=y; add(x,n); add(n,x); fa[n]=x;
			if (b[belong[x]].size==blo)
			    belong[n]=++cnt,b[cnt].ins(y),Badd(belong[x],cnt);
			else b[belong[n]=belong[x]].ins(y);
		}
	}
}
