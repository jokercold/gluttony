#include<iostream>
#include<cstdio>
using namespace std;
#define N 200010
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
int main(){
  int n;
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
	  int x;
		scanf("%d",&x);
		Next[i]=f[i]=min(i+x,n+1);
		//cout<<f[i]<<endl;
		siz[i]=1;
	}
	siz[n+1]=1;
	int m;
	scanf("%d",&m);
	while (m--){
	  int op;
		scanf("%d",&op);
		if (op==1){
		  reverse(n+1);
			int x;
			scanf("%d",&x);
			++x;
			//cout<<x<<endl;
			access(x);splay(x);
			//cout<<ch[x][0]<<" "<<ch[x][1]<<endl;
			printf("%d\n",siz[ch[x][0]]);
		}else{
		  int x,y;
			scanf("%d%d",&x,&y);
			x++;
			int tmp=min(x+y,n+1);
			cut(x,Next[x]);
			link(x,tmp);
			Next[x]=tmp;
		}
	}
	return 0;
}
