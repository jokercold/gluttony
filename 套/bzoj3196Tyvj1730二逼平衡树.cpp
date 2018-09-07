#include<iostream>
#include<cstdio>
using namespace std;
#define Maxn 2000000
int sz,n;
int h[Maxn];
int root[Maxn];
namespace Splay{	
	int f[Maxn];
	int ch[Maxn][2];
	int key[Maxn];	
	int id[Maxn];
	int cnt[Maxn];	
	int siz[Maxn];	
	void clear(int x){
		ch[x][0]=ch[x][1]=f[x]=cnt[x]=key[x]=siz[x]=0;
	}
	void update(int x){
		siz[x]=cnt[x];
		if (ch[x][0]) siz[x]+=siz[ch[x][0]];
		if (ch[x][1]) siz[x]+=siz[ch[x][1]];
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
		while(x!=k){
			int y=f[x],z=f[y];
			if(y!=k){
				if(ch[y][0]==x^ch[z][0]==y) rotate(x,k);
				else rotate(y,k);
			}
			rotate(x,k);
		}	
	}
	void create(int v){
		sz++;
		ch[sz][0]=ch[sz][1]=f[sz]=0;
		key[sz]=v;
		cnt[sz]=1;
		siz[sz]=1;
	}  
	void insert(int &root,int v){
		if (!root)
			create(v),root=sz;
		else{
			int now=root,fa=0;
			while(1){
				if (key[now]==v){
			   	cnt[now]++;
					update(now);update(fa);
					splay(now,root);
					break;
				}
				fa=now;
				now=ch[fa][v>key[fa]];
				if (!now){
					create(v);
					f[sz]=fa;
					ch[fa][v>key[fa]]=sz;
					update(fa);
					splay(sz,root);
					break;
				}
			}
		}
	}
	int findpos(int &root,int v){
		int now=root,ans=0;
		//cout<<now<<endl;
		while(now){
			//cout<<now<<endl;
			if (v<key[now])
				now=ch[now][0];
			else{
				ans+=ch[now][0]?siz[ch[now][0]]:0;
				if (v==key[now]){
					splay(now,root);
					return ans+1;
				}
				ans+=cnt[now];
				now=ch[now][1];
			}
		}
		return ans+1;
	}
	int pre(int &root){
		int now=ch[root][0];
		while(ch[now][1])
			now=ch[now][1];
		return now;
	}
	int nex(int &root){
		int now=ch[root][1];
		while(ch[now][0])
			now=ch[now][0];
		return now;
	}
	void del(int &root,int x){
		int t=findpos(root,x);
		if (cnt[root]>1){
			cnt[root]--;
			//cout<<cnt[root]<<endl;
			update(root);
			return;
		}
		if (!ch[root][0] && !ch[root][1]){
			clear(root);
			root=0;
			return;
		}
		if (!ch[root][1]){
			int temp=root;
			root=ch[root][0];
			f[root]=0;
			clear(temp);
			return;
		}
		else
		if (!ch[root][0]){
			int temp=root;
			root=ch[root][1];
			f[root]=0;
			clear(temp);
			return;
		}
		int pre1=pre(root),temp=root;
		splay(pre1,root);
		f[ch[temp][1]]=root;
		ch[root][1]=ch[temp][1];
		clear(temp);
		update(root);
	}
}
void build(int p,int l,int r){
  for (int i=l;i<=r;++i) Splay::insert(root[p],h[i]);
	//cout<<p<<" "<<l<<" "<<r<<" "<<root[p]<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
int queryx_pos(int p,int l,int r,int x,int y,int k){
	if (l>y||r<x||root[p]==0) return 0;
	//cout<<root[p]<<endl;
	if (x<=l&&r<=y) return Splay::findpos(root[p],k)-1;
	int mid=(l+r)>>1;
	//cout<<p<<" "<<l<<" "<<r<<" "<<x<<" "<<y<<endl;
	return queryx_pos(p<<1,l,mid,x,y,k)+queryx_pos(p<<1|1,mid+1,r,x,y,k);
}
int querypos_x(int l,int r,int k){
  int L=0,R=100000000;
	while (L<R){
		//cout<<L<<" "<<R<<endl;
	  int mid=(L+R)>>1;
		//cout<<mid<<" "<<queryx_pos(1,1,n,l,r,mid)<<endl;
		if (queryx_pos(1,1,n,l,r,mid)<k) L=mid+1;
		else R=mid;
	}
	return L-1;
}
void change(int p,int l,int r,int x,int yh,int k){
  Splay::del(root[p],yh);
	Splay::insert(root[p],k);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (mid>=x) change(p<<1,l,mid,x,yh,k);
	else change(p<<1|1,mid+1,r,x,yh,k);
}
int querypre(int p,int l,int r,int x,int y,int k){
  if (l>y||r<x||root[p]==0) return -1<<29;
	if (x<=l&&r<=y){
		Splay::insert(root[p],k);
	  int ans=Splay::key[Splay::pre(root[p])];
		Splay::del(root[p],k);
		if (ans==0) return -1<<29;
		//cout<<l<<" "<<r<<" "<<k<<" "<<ans<<endl;
		return ans;
  }
	int mid=(l+r)>>1;
	return max(querypre(p<<1,l,mid,x,y,k),querypre(p<<1|1,mid+1,r,x,y,k));
}
int queryaft(int p,int l,int r,int x,int y,int k){
  if (l>y||r<x||root[p]==0) return 1<<29;
	if (x<=l&&r<=y){
		Splay::insert(root[p],k);
	  int ans=Splay::key[Splay::nex(root[p])];
		Splay::del(root[p],k);
		if (ans==0) return 1<<29;
		//cout<<ans<<endl;
		return ans;
	}
	int mid=(l+r)>>1;
	return min(queryaft(p<<1,l,mid,x,y,k),queryaft(p<<1|1,mid+1,r,x,y,k));
}
int main(){
	sz=0;
  int m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&h[i]);
	build(1,1,n);
	for (int i=1;i<=m;++i){
		//cout<<i<<endl;
	  int opt,l,r,k;
		scanf("%d",&opt);
		if (opt==1){scanf("%d%d%d",&l,&r,&k);printf("%d\n",queryx_pos(1,1,n,l,r,k)+1);}
		if (opt==2){scanf("%d%d%d",&l,&r,&k);printf("%d\n",querypos_x(l,r,k));}
		if (opt==3){
			scanf("%d%d",&l,&k);
			int yh=h[l];
			h[l]=k;
			//cout<<yh<<endl;
			change(1,1,n,l,yh,k);
		}
		if (opt==4){scanf("%d%d%d",&l,&r,&k);printf("%d\n",querypre(1,1,n,l,r,k));}
		if (opt==5){scanf("%d%d%d",&l,&r,&k);printf("%d\n",queryaft(1,1,n,l,r,k));}
	}
	return 0;
}
