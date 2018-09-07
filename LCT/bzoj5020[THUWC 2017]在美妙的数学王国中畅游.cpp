#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define db double
#define N 100100
char ss[30];
bool rev[N];
int st[N],ch[N][2],f[N];
db inv[20];
struct func{
	db v[20];
	void init(int F,db A,db B){
	  if (F==1){
		  db s[4]={sin(B),cos(B),-sin(B),-cos(B)};
		  db y=1;
			for (int i=0;i<=17;++i) 
				v[i]=s[i%4]*y*inv[i],y=y*A;
		}else if (F==2){
		  db y=exp(B);
			for (int i=0;i<=17;++i)
				v[i]=y*inv[i],y=y*A;
		}else{
		  v[0]=B;
			v[1]=A;
			for (int i=2;i<=17;++i)
				v[i]=0;
		}
	}
	db get(db A){
	  db ans=0;
		for (int i=17;i>=0;--i) ans=ans*A+v[i];
		return ans;
	}
}val[N],sum[N];
void update(int x){
  for (int i=0;i<=17;++i)
		sum[x].v[i]=sum[ch[x][0]].v[i]+sum[ch[x][1]].v[i]+val[x].v[i];
}
void pushdown(int x){
  if (rev[x]){
	  swap(ch[x][0],ch[x][1]);
		rev[ch[x][0]]^=1;rev[ch[x][1]]^=1;
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
void makeroot(int x){
  access(x);splay(x);rev[x]^=1;
}
void link(int u,int v){
  makeroot(u);
	f[u]=v;
}
void cut(int u,int v){
  makeroot(u);
	access(v);
	splay(v);
	ch[v][0]=f[u]=0;
}
int find(int x){
  access(x);
	splay(x);
	int y=x;
	while (ch[y][0]) y=ch[y][0];
	return y;
}
int main(){
	inv[0]=1.0;
	for (int i=1;i<=17;++i) inv[i]=inv[i-1]/i;
  int n,m;
	scanf("%d%d",&n,&m);
  scanf("%s",ss);
	for (int i=1;i<=n;++i){
		int F;
    db A,B;
		scanf("%d%lf%lf",&F,&A,&B);
		val[i].init(F,A,B);
	}
	while (m--){
	  scanf("%s",ss);
		if (ss[0]=='a'){
		  int u,v;
			scanf("%d%d",&u,&v);++u;++v;
			link(u,v);
		}else if (ss[0]=='d'){
		  int u,v;
			scanf("%d%d",&u,&v);++u;++v;
			cut(u,v);
		}else if (ss[0]=='m'){
		  int C,F;
			db A,B;
			scanf("%d%d%lf%lf",&C,&F,&A,&B);
			++C;
			access(C);
			splay(C);
			val[C].init(F,A,B);
		}else if (ss[0]=='t'){
		  int u,v;
			db x;
			scanf("%d%d%lf",&u,&v,&x);++u;++v;
			if (find(u)!=find(v)){
			  printf("unreachable\n");
				continue;
			}
			makeroot(u);
			access(v);
			splay(v);
			printf("%.8le\n",sum[v].get(x));
		}
	}
	return 0;
}
