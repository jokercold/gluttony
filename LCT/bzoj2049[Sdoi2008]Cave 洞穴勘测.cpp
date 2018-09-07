#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){
  char ch=getchar();
	while (ch<'0'||ch>'9')ch=getchar();
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	return tmp;
}
#define N 200010
char opt[20];
int ch[N][2],siz[N],rev[N],Next[N],f[N],stack[N];
bool isroot(int x){
  return(ch[f[x]][0]!=x&&ch[f[x]][1]!=x);
}
void update(int x){
	if (x){
		siz[x]=1;
		if (ch[x][0]) siz[x]+=siz[ch[x][0]];
		if (ch[x][1]) siz[x]+=siz[ch[x][1]];
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
	for (int i=x;!isroot(i);i=f[i])
		  stack[++top]=f[i];
	for (int i=top;i;i--) pushdown(stack[i]);
	//cout<<top<<endl;
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
int main(){
  int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i){
	  scanf("%s",opt);
    int x,y;
		x=read();y=read();
		if (opt[0]=='Q'){
			if (find(x)==find(y)) printf("Yes\n");
			else printf("No\n");
		}
		if (opt[0]=='C') link(x,y);
		if (opt[0]=='D') cut(x,y);
	}
	return 0;
}
