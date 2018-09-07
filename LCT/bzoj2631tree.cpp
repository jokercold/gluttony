#include<iostream>
#include<cstdio>
using namespace std;
#define N 100500
#define M 51061
unsigned int sum[N],v[N],add[N],mult[N],siz[N],st[N];
int ch[N][2],f[N];
bool rev[N];
char ss[10];
bool isroot(int x){
  return (ch[f[x]][1]!=x&&ch[f[x]][0]!=x);
}
void update(int x){
  int l=ch[x][0],r=ch[x][1];
	sum[x]=(sum[l]+sum[r]+v[x])%M;
  siz[x]=(siz[l]+siz[r]+1)%M;
}
void cal(int x,int mu,int ad){
	if (!x) return;
  //cout<<v[x]<<" "<<sum[x]<<" "<<mult[x]<<" "<<add[x]<<endl;
	//cout<<mu<<" "<<ad<<endl;
  v[x]=(v[x]*mu+ad)%M;
  sum[x]=(sum[x]*mu+siz[x]*ad)%M;
	mult[x]=mult[x]*mu%M;
	add[x]=(add[x]*mu+ad)%M;
	//cout<<x<<" "<<mu<<" "<<ad<<endl;
	//cout<<v[x]<<" "<<sum[x]<<" "<<mult[x]<<" "<<add[x]<<endl;
}
void pushdown(int x){
  int l=ch[x][0],r=ch[x][1];
  if (rev[x]){
	  rev[l]^=1;rev[r]^=1;rev[x]^=1;
		swap(ch[x][0],ch[x][1]);
	}
	int mu=mult[x],ad=add[x];
	//cout<<x<<" "<<ch[x][0]<<" "<<ch[x][1]<<endl;
	mult[x]=1;
	add[x]=0;
	if (mu!=1||ad!=0){
	  cal(ch[x][0],mu,ad);
		cal(ch[x][1],mu,ad);
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
  access(x);
	splay(x);
	rev[x]^=1;
}
void link(int x,int y){
  reverse(x);
	f[x]=y;
}
void cut(int x,int y){
  reverse(x);
	access(y);
	splay(y);
	ch[y][0]=f[x]=0;
}
int main(){
  int n,q;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;++i){
	  siz[i]=1;
		mult[i]=1;
		add[i]=0;
		sum[i]=1;
		v[i]=1;
	}
	for (int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
	  link(u,v);
	}	
	while (q--){
		scanf("%s",ss);
		if (ss[0]=='+'){
		  int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
      reverse(u);
			access(v);
			splay(v);
			cal(v,1,c);
		}
		if (ss[0]=='-'){
		  int u,v;
			scanf("%d%d",&u,&v);cut(u,v);
		  scanf("%d%d",&u,&v);link(u,v);
		}
		if (ss[0]=='*'){
		  int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			reverse(u);
      access(v);
			splay(v);
			cal(v,c,0);
		}
    if (ss[0]=='/'){
		  int u,v;
			scanf("%d%d",&u,&v);
			reverse(u);
			access(v);
			splay(v);
			printf("%d\n",sum[v]);
		}
	}
	return 0;
}
