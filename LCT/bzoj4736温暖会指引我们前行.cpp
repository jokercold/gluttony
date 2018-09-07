#include<stdio.h>
#include<iostream>
using namespace std;
inline int read(){
  char ch=getchar();
  while (ch<'0'||ch>'9') ch=getchar();
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+(ch-'0');ch=getchar();}
	return tmp;
}
#define N 400050
int tim[N],sum[N],mn[N],ch[N][2],f[N],len[N],rev[N],st[N];
char ss[30];
inline void update(int x){
  int l=ch[x][0],r=ch[x][1];
  sum[x]=sum[l]+sum[r]+len[x];
	mn[x]=x;
	if (tim[mn[x]]>tim[mn[l]]) mn[x]=mn[l];
	if (tim[mn[x]]>tim[mn[r]]) mn[x]=mn[r];
}
inline void pushdown(int x){
  int l=ch[x][0],r=ch[x][1];
  if (x&&rev[x]){
	  rev[l]^=1;rev[r]^=1;
		rev[x]^=1;
		swap(ch[x][0],ch[x][1]);
	}
}
inline bool isroot(int x){
  return (ch[f[x]][0]!=x&&ch[f[x]][1]!=x);
}
inline void rotate(int x){
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
	for(int i=x;!isroot(i);i=f[i]) st[++top]=f[i];
	for(;top;top--) pushdown(st[top]);
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
inline void reverse(int x){
  access(x);
	splay(x);
	rev[x]^=1;
}
inline void link(int x,int y){
  reverse(x);
	f[x]=y;
	splay(x);
}
inline void cut(int x,int y){
  reverse(x);
	access(y);
	splay(y);
	ch[y][0]=f[x]=0;
	update(y);
}
int find(int x){
  access(x);
	splay(x);
	int y=x;
	while (ch[y][0]) y=ch[y][0];
	return y;
}
inline int query(int x,int y){
  reverse(x);
	access(y);
	splay(y);
	return mn[y];
}
int main(){
  int n,m;
	n=read();m=read();
	for (int i=0;i<=n;++i) tim[i]=1<<29,mn[i]=i,len[i]=0;
	while (m--){
	  scanf("%s",ss);
		if (ss[0]=='f'){
		  int id,u,v;
			id=read();id+=n+1;;
		 	u=read();v=read();tim[id]=read();len[id]=read();
			mn[id]=id;
      ++u;++v;
			if (find(u)==find(v)){
			  int x=query(u,v);
				if (tim[x]<tim[id]){
				  cut(u,x);cut(v,x);
					link(u,id);link(v,id);
				}
			}else	link(u,id),link(v,id);
		}
		if (ss[0]=='m'){
		  int u,v;
			u=read();v=read();
			++u;++v;
			if (find(u)!=find(v)) printf("-1\n");
			else{
			  reverse(u);
				access(v);
				splay(v);
				printf("%d\n",sum[v]);
			}
		}
		if (ss[0]=='c'){
		  int id,l;
		  id=read();l=read(); 			
			id+=n+1;
			splay(id);
			len[id]=l;
      update(id);
		}
	}
	return 0;
}

