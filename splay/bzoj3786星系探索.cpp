#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){
  char last='+',ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') last='-';ch=getchar();}
	int tmp=0;
	while (ch>='0'&&ch<='9')tmp=tmp*10+(ch-'0'),ch=getchar();
	if (last=='-') tmp=-tmp;
	return tmp;
}
#define N 300000
#define ll long long
int id,num,root;
int vet[N],Next[N],hed[N];
int ch[N][2],siz[N],v[N],f[N],IN[N],OUT[N],tt[N],list[N],st[N],tag[N],yh[N];
ll sum[N];
inline void add(int u,int v){
  ++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
inline void update(int x){
  int l=ch[x][0],r=ch[x][1];
	yh[x]=yh[l]+yh[r]+1;
	siz[x]=siz[l]+siz[r]+tt[x];
	sum[x]=sum[l]+sum[r]+list[x];
}
inline void pushdown(int x){
  int l=ch[x][0],r=ch[x][1];
	if (tag[x]){
	  tag[l]+=tag[x];
		list[l]+=tt[l]*tag[x];
		sum[l]+=(ll)siz[l]*tag[x];
		tag[r]+=tag[x];
		list[r]+=tt[r]*tag[x];
		sum[r]+=(ll)siz[r]*tag[x];
		tag[x]=0;
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
  int top=0;
	st[++top]=x;
	for (int i=x;f[i];i=f[i]) st[++top]=f[i];
	for (;top;top--) pushdown(st[top]);
	while (x!=k){
	  int y=f[x],z=f[y];
		if (y!=k){
		  if (ch[y][0]==x^ch[z][0]==y) rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
inline int split(int l,int r){
	//cout<<l<<" "<<r<<endl;
  int x=l,y=r;
	splay(x,root);splay(y,ch[x][1]);
	return y;
}
void dfs(int u,int fa){
  IN[u]=++id;
	tt[id]=1;
	yh[id]=1;
	list[id]=v[u];
	for (int i=hed[u];i!=-1;i=Next[i]){
		int v=vet[i];
		if (v==fa) continue;
		dfs(v,u);
	}
	OUT[u]=++id;
	tt[id]=-1;
	yh[id]=1;
	list[id]=-v[u];
}
void build(int l,int r,int last){
  if (l>r) return;
	int mid=(l+r)>>1;
	if (l==r){
		sum[l]=list[l];
		yh[l]=1;
		siz[l]=tt[l];
	}else build(l,mid-1,mid),build(mid+1,r,mid);
	f[mid]=last;
	update(mid);
	ch[last][mid>=last]=mid;
}
inline int Pre(int x){
  splay(x,root);
	int id=ch[x][0];
	while (ch[id][1]) id=ch[id][1];
	return id;
}
inline int Last(int x){
  splay(x,root);
	int id=ch[x][1];
	while (ch[id][0]) id=ch[id][0];
	return id;
}
int main(){
  int n;
	scanf("%d",&n);
	num=0;
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=2;i<=n;++i){
	  int u;
		u=read();
		add(i,u);
		add(u,i);
	}
	for (int i=1;i<=n;++i) v[i]=read();
	id=1;
	dfs(1,0);
	++id;
	build(1,id,0);
	root=(1+id)>>1;
	int m;
	m=read();
	while (m--){
	  char ss[5];
		scanf("%s",ss);
		if (ss[0]=='Q'){
      int d;
			d=read();
			int y=split(1,Last(IN[d]));
			printf("%lld\n",sum[ch[y][0]]);
		}
		if (ss[0]=='C'){
			int a,b;
			a=read();b=read();
			int x=split(Pre(IN[a]),Last(OUT[a]));
	    int z=ch[x][0];
			f[ch[x][0]]=0;ch[x][0]=0;
			update(x);update(f[x]);
			int k=IN[b],y=Last(k);
			splay(k,root);
			splay(y,ch[k][1]);
			//cout<<ch[y][0]<<endl;
      ch[y][0]=z;
			f[ch[y][0]]=y;
			update(y);update(f[y]);
		}
		if (ss[0]=='F'){
		  int p,q;
			p=read();q=read();
			int x=split(Pre(IN[p]),Last(OUT[p]));
			int y=ch[x][0];
			tag[y]+=q;
			list[y]+=tt[y]*q;
			sum[y]+=(ll)siz[y]*q;
			update(x);
			update(f[x]);
		}
		//cout<<"YES"<<endl;
	}
	return 0;
}
