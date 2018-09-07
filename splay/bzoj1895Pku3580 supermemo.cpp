#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 200000
int a[N];
char ss[40];
int root,sz;
namespace Splay{
	int siz[N],Min[N],rev[N],f[N],ch[N][2],v[N],tag[N];
  void update(int x){
	  siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
		Min[x]=v[x];
		if (ch[x][0]) Min[x]=min(Min[x],Min[ch[x][0]]);
		if (ch[x][1]) Min[x]=min(Min[x],Min[ch[x][1]]);
	}
	void pushdown(int x){
	  if (rev[x]){
		  swap(ch[x][0],ch[x][1]);
			rev[ch[x][0]]^=1;rev[ch[x][1]]^=1;
			rev[x]=0;
		}
		if (ch[x][0]){
			tag[ch[x][0]]+=tag[x];
			v[ch[x][0]]+=tag[x];
			Min[ch[x][0]]+=tag[x];
		}
		if (ch[x][1]){
			tag[ch[x][1]]+=tag[x];
			v[ch[x][1]]+=tag[x];
			Min[ch[x][1]]+=tag[x];
		}
		tag[x]=0;
	}
  void rotate(int x,int &k){
	  int y=f[x],z=f[y],l,r;
		l=(ch[y][1]==x);r=l^1;
		if (y==k) k=x;
		else ch[z][ch[z][1]==y]=x;
		f[x]=z;f[y]=x;f[ch[x][r]]=y;
		ch[y][l]=ch[x][r];ch[x][r]=y;
		update(y);update(x);
	}
	void splay(int x,int &k){
	  while (x!=k){
		  int y=f[x],z=f[y];
			if (y!=k){
			  if (ch[y][0]==x^ch[z][0]==y) rotate(x,k);
				else rotate(y,k);
			}
			rotate(x,k);
		  //cout<<x<<" "<<y<<" "<<z<<" "<<endl;
			//cout<<x<<" "<<k<<endl;
		}
	}
	int findx(int x){
	  int now=root;
		while (1){
			//cout<<now<<" "<<siz[ch[now][0]]<<endl;
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
	void reverse(int l,int r){
		//cout<<l<<" "<<r<<endl;
		int x=findx(l);
		//cout<<"x=="<<" "<<x<<endl;
		int y=findx(r+2);
		//cout<<"y=="<<" "<<y<<endl;
		splay(x,root); 
		//cout<<x<<" "<<"OK"<<endl;
		//cout<<ch[x][1]<<endl;
		splay(y,ch[x][1]);
		//cout<<y<<" "<<"OK"<<endl;
		int z=ch[y][0];
		rev[z]^=1;
		//cout<<"end"<<endl;
	}
	void build(int l,int r,int fa){
	  if (l>r) return;
		int mid=(l+r)>>1,now=mid,last=fa;
		if (l==r){
		  siz[now]=1;
		}else build(l,mid-1,mid),build(mid+1,r,mid);
		v[now]=a[mid];
		Min[now]=a[mid];
		f[now]=last;
		update(now);
		ch[last][mid>=fa]=now;
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
  using namespace Splay;
  memset(Min,127,sizeof(Min));
  memset(v,127,sizeof(v));
  int n;
	scanf("%d",&n);
	for (int i=2;i<=n+1;++i) scanf("%d",&a[i]);
	a[1]=-1<<29;a[n+2]=1<<29;
	sz=n+2;
	build(1,n+2,0);
	root=(n+3)>>1;
  int m;
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
		scanf("%s",ss);
		//cout<<i<<" "<<ss[0]<<endl;
		//cout<<ss[0]<<endl;
		if (ss[0]=='A'){
		  int l,r,D;
			scanf("%d%d%d",&l,&r,&D);
			//cout<<"hk"<<endl;
			int x=findx(l),y=findx(r+2);
			//cout<<"hgz"<<endl;
      splay(x,root); splay(y,ch[x][1]);
			int z=ch[y][0];
			tag[z]+=D;
			Min[z]+=D;
			v[z]+=D;
		}else if (ss[0]=='R'){
			if (ss[3]=='E'){
			  int l,r;
				scanf("%d%d",&l,&r);
				reverse(l,r);
			}else{
			  int l,r,t;
        scanf("%d%d%d",&l,&r,&t);
			  //cout<<l<<" "<<r<<" "<<t<<endl;
				t=(t%(r-l+1)+r-l+1)%(r-l+1);
				//cout<<l<<" "<<r<<" "<<t<<endl;
				if (!t) continue;
  			reverse(l,r);
				reverse(l,l+t-1);
				reverse(l+t,r);
			}
		}else if (ss[0]=='I'){
		  int l,r,t;
			scanf("%d%d",&l,&t);
			int x=findx(l+1),y=findx(l+2);
			splay(x,root); splay(y,ch[x][1]);
			++sz;
			ch[y][0]=sz;
			f[sz]=y;
			v[sz]=t;
			rev[sz]=0;
			siz[sz]=1;
			Min[sz]=t;
			update(y);
			if (f[y]) update(f[y]);
		}else if (ss[0]=='D'){
		  int l,r,t;
			scanf("%d",&t);
			int x=findx(t),y=findx(t+2);
			splay(x,root); splay(y,ch[x][1]);
			int sb=ch[y][0];
			ch[y][0]=0;
			Min[sb]=1<<30;
			v[sb]=1<<30;
			f[sb]=0;
			rev[sb]=0;
			siz[sb]=0;
			update(y);
			if (f[y]) update(f[y]);
		}else if (ss[0]=='M'){
		  int l,r;
			scanf("%d%d",&l,&r);
			int x=findx(l),y=findx(r+2);
			splay(x,root); splay(y,ch[x][1]);
			printf("%d\n",Min[ch[y][0]]);
		}
		//cout<<i<<endl;
	}
	return 0;
}	
