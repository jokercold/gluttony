#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 600000
char ss[100];
int tail,root;
int stack[N+100];
int c[N];
namespace Splay{
	int sum[N],ch[N][2],mx[N],lx[N],rx[N],tag[N],rev[N],siz[N],v[N],id[N],f[N];
	void update(int x){
	  int l=ch[x][0],r=ch[x][1];
		sum[x]=sum[l]+sum[r]+v[x];
		siz[x]=siz[l]+siz[r]+1;
		mx[x]=max(mx[l],mx[r]);
		mx[x]=max(mx[x],rx[l]+v[x]+lx[r]);
		lx[x]=max(lx[l],sum[l]+v[x]+lx[r]);
		rx[x]=max(rx[r],sum[r]+v[x]+rx[l]);
		/*cout<<"x=="<<x<<endl;
		cout<<"mx[x]=="<<mx[x]<<endl;
		cout<<"lx[x]=="<<lx[x]<<endl;
		cout<<"rx[x]=="<<rx[x]<<endl;*/
	} 
	void pushdown(int x){
	  int l=ch[x][0],r=ch[x][1];
		if (tag[x]){
			rev[x]=tag[x]=0;
			if (l) tag[l]=1,v[l]=v[x],sum[l]=v[x]*siz[l];
			if (r) tag[r]=1,v[r]=v[x],sum[r]=v[x]*siz[r];
			if (v[x]>=0){
			  if (l) lx[l]=rx[l]=mx[l]=sum[l];
				if (r) lx[r]=rx[r]=mx[r]=sum[r];
			}else{
			  if (l) lx[l]=rx[l]=0,mx[l]=v[x];
				if (r) lx[r]=rx[r]=0,mx[r]=v[x];
			}
		}
		if (rev[x]){
		  rev[l]^=1;rev[r]^=1;rev[x]=0;
			swap(lx[l],rx[l]);swap(lx[r],rx[r]);
			swap(ch[l][0],ch[l][1]);swap(ch[r][0],ch[r][1]);
		}
	}
  void clear(int x){
	  siz[x]=0;
		sum[x]=0;
		mx[x]=-1<<29;
		lx[x]=rx[x]=v[x]=0;
		tag[x]=0;
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
	  while(x!=k){
		  int y=f[x],z=f[y];
			if (y!=k){
			  if (ch[y][0]==x^ch[z][0]==y) rotate(x,k);
				else rotate(y,k);
			}	
			//cout<<x<<" "<<y<<" "<<z<<endl;
			rotate(x,k);
		}
	}
	int findx(int x){
	  int now=root;
		while (1){
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
  int split(int l,int r){
	  int x=findx(l),y=findx(r);
		splay(x,root);splay(y,ch[x][1]);
		return y;
	}
	void dfs(int &x){
		clear(x);
		++tail;
		stack[tail]=x;
	  if (ch[x][0]) dfs(ch[x][0]);
		if (ch[x][1]) dfs(ch[x][1]);
		x=0;
	}
	void build(int l,int r,int fa){
	  if (l>r) return;
		int mid=(l+r)>>1,now=id[mid],last=id[fa];
		if (l==r){
      sum[now]=c[l];siz[now]=1;
			tag[now]=rev[now]=0;
			if (c[l]>=0) lx[now]=rx[now]=mx[now]=c[l];
			else lx[now]=rx[now]=0,mx[now]=c[l];
		}else build(l,mid-1,mid),build(mid+1,r,mid);
		v[now]=c[mid];f[now]=last;tag[now]=0;rev[now]=0;
		update(now);
		ch[last][mid>=fa]=now;
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	using namespace Splay;
	memset(mx,-127,sizeof(mx));
  int n,m;
	scanf("%d%d",&n,&m);
	tail=0;
	for (int i=600000;i>=1;--i){
    ++tail;
		stack[tail]=i;
	}
	for (int i=2;i<=n+1;++i) scanf("%d",&c[i]);
	c[1]=-1<<29;
	c[n+2]=-1<<29;
	id[0]=0;
	for (int i=1;i<=n+2;++i) id[i]=stack[tail--];//cout<<id[i]<<endl;
	//cout<<stack[tail]<<endl;
	build(1,n+2,0);
	root=(n+3)>>1;
	while (m--){
		//cout<<m<<endl;
	  scanf("%s",ss);
		//cout<<"YES"<<endl;
		if (ss[0]=='I'){
		  int pos,tot;
			scanf("%d%d",&pos,&tot);
		  for (int i=1;i<=tot;++i){
			  scanf("%d",&c[i]);
	      id[i]=stack[tail--];
				//cout<<id[i]<<endl;
			}
			//cout<<id[1]<<endl;
			build(1,tot,0);
			int RT=(1+tot)>>1;
			int y=split(pos+1,pos+2);
			//cout<<"YES"<<endl;
			ch[y][0]=id[RT];
			f[id[RT]]=y;
			update(y);update(f[y]);
		}else if(ss[0]=='D'){
	  	int pos,tot;
			scanf("%d%d",&pos,&tot);
			int l=pos,r=pos+tot-1;
			int y=split(l,r+2);
		  dfs(ch[y][0]);
			update(y);update(f[y]);
		}else if (ss[0]=='M'&&ss[2]=='K'){
	    int pos,tot,c;
			scanf("%d%d%d",&pos,&tot,&c);
			int l=pos,r=pos+tot-1;
			int y=split(l,r+2);
			int z=ch[y][0];
			tag[z]=1;v[z]=c;sum[z]=v[z]*siz[z];
			if (v[z]>=0){
			  lx[z]=rx[z]=mx[z]=sum[z];
			}else lx[z]=rx[z]=0,mx[z]=v[z];
      update(y);update(f[y]);
		}else if (ss[0]=='R'){
		  int pos,tot;
			scanf("%d%d",&pos,&tot);
			int l=pos,r=pos+tot-1;
			int y=split(l,r+2);
			int z=ch[y][0];
			rev[z]^=1;
		  swap(ch[z][0],ch[z][1]);
		  swap(lx[z],rx[z]);
			update(y);update(f[y]);
		}else if (ss[0]=='G'){
		  int pos,tot;
			scanf("%d%d",&pos,&tot);
			int l=pos,r=pos+tot-1;		
			int y=split(l,r+2);
			//cout<<"YES"<<endl;
  		printf("%d\n",sum[ch[y][0]]);
		}else printf("%d\n",mx[root]);
	}
	return 0;
}
