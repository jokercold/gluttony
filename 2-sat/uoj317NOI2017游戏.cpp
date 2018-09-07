#include<bits/stdc++.h>
using namespace std;
inline char getch(){
	char ch=getchar();
	while ((ch<'A'||ch>'Z')&&(ch<'a'||ch>'z')) ch=getchar();
	return ch;
}
#define N 200100
struct node{
	int x,y,IDx,IDy;
}a[N];
int cnt,n,divg,tim,TT,m;
int ID[N];
int vet[N],Next[N],hed[N],dfn[N],low[N],st[N],ans[N],bel[N],num[N][4];
bool flag[N];
void add(int u,int v){
	if (u<0||v<0) return;
	++cnt;
	vet[cnt]=v;
	Next[cnt]=hed[u];
	hed[u]=cnt;
}
void Tarjan(int u){
  dfn[u]=low[u]=++tim;
	st[++TT]=u;
	flag[u]=true;
	for (int i=hed[u];i!=-1;i=Next[i]){
		int v=vet[i];
		if (!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if (flag[v]) low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]==low[u]){
	  ++divg;
		while (st[TT]!=u){
			int tmp=st[TT];
			--TT;
			flag[tmp]=false;
			bel[tmp]=divg;
		}
		--TT;
		flag[u]=false;
		bel[u]=divg;
	}
}
bool Two_sat(){
  cnt=0;
	for (int i=0;i<=n+n;++i) hed[i]=-1;
	for (int i=1;i<=m;++i){
		int x=a[i].x,y=a[i].y,IDx=a[i].IDx,IDy=a[i].IDy;
		if (IDx==ID[x]) continue;
		if (IDy==ID[y]) add(num[x][IDx],num[x][IDx]^1);
		add(num[x][IDx],num[y][IDy]);
		add(num[y][IDy]^1,num[x][IDx]^1);
	}
	for (int i=0;i<=n+n;++i) dfn[i]=low[i]=0,flag[i]=false;
	divg=0;
	tim=0;TT=0;
	for (int i=0;i<n+n;++i)
	if (!dfn[i]) Tarjan(i);
	for (int i=0;i<n+n;i+=2)
  if (bel[i]==bel[i^1]) return false;
	else	if (bel[i]<bel[i^1]) ans[i/2]=i;else ans[i/2]=i^1;
	return true;
}
bool Dfs(int tt=0){
	if (tt==n) return Two_sat();
	if (ID[tt]<3) return Dfs(tt+1);
	num[tt][ID[tt]=0]=-1;num[tt][1]=tt<<1;num[tt][2]=tt<<1^1;
	if (Dfs(tt+1)) return true;
	num[tt][ID[tt]=1]=-1;num[tt][0]=tt<<1;num[tt][2]=tt<<1^1;
	bool f=Dfs(tt+1);
	ID[tt]=3;
	return f;
}
int main(){
	int D;
	scanf("%d%d",&n,&D);
  for (int i=0;i<n;++i) switch(getch()){
		case 'a':num[i][ID[i]=0]=-1;num[i][1]=i<<1;num[i][2]=i<<1^1;break;
		case 'b':num[i][ID[i]=1]=-1;num[i][0]=i<<1;num[i][2]=i<<1^1;break;
		case 'c':num[i][ID[i]=2]=-1;num[i][0]=i<<1;num[i][1]=i<<1^1;break;
		case 'x':ID[i]=3;break;
	}
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
	  scanf("%d",&a[i].x);a[i].x--;
		a[i].IDx=getch()-'A';
		scanf("%d",&a[i].y);a[i].y--;
		a[i].IDy=getch()-'A';
	}
	if (!Dfs()) return printf("-1\n"),0;
	for (int i=0;i<n;++i)
		for (int j=0;j<3;++j)
			if (ans[i]==num[i][j]) putchar('A'+j);
	printf("\n");
	return 0;
}
