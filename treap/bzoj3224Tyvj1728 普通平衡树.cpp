#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define mp make_pair
typedef pair<int,int> par;
#define N 100010
namespace Treap{
	int cnt=0,root=0;
  struct node{
	  int ls,rs,data,key,size;
	}T[N];
	void update(int x){
	  T[x].size=T[T[x].ls].size+T[T[x].rs].size+1;
	}
	par split(int x,int n){
		if (n==0) return mp(0,x);
		int ls=T[x].ls,rs=T[x].rs;
    if (n==T[ls].size) return T[x].ls=0,update(x),mp(ls,x);
		if (n==T[ls].size+1) return T[x].rs=0,update(x),mp(x,rs);
		if (n<T[ls].size){
		  par tmp=split(ls,n);
      return T[x].ls=tmp.second,update(x),mp(tmp.first,x);
		}
		par tmp=split(rs,n-T[ls].size-1);
		return T[x].rs=tmp.first,update(x),mp(x,tmp.second);
	}
	int merge(int x,int y){
	  if (x==0||y==0) return x+y;
		if (T[x].key<T[y].key) return T[x].rs=merge(T[x].rs,y),update(x),x;
		else return T[y].ls=merge(x,T[y].ls),update(y),y;
	}
	int findpos(int x){
		int now=root;
	  int ans=0,tmp=(int)1e9;
		while (now){
		  if (x==T[now].data) tmp=min(tmp,ans+T[T[now].ls].size+1);
			if (x>T[now].data) ans+=T[T[now].ls].size+1,now=T[now].rs;
			else now=T[now].ls;
		}
		return tmp==(int)1e9?ans:tmp;
	}
	int findx(int x){
	  int now=root;
		while (true){
		  if (T[T[now].ls].size>x-1) now=T[now].ls;
			else{
			  x=x-T[T[now].ls].size-1;
        if (!x) return T[now].data;
				now=T[now].rs;
			}
		}
	}
	int pre(int x){
	  int ans=-(int)1e9;
		int now=root;
		while (now){
		  if (T[now].data<x) ans=max(ans,T[now].data),now=T[now].rs;
			else now=T[now].ls;
		}
		return ans;
	}
	int neg(int x){
	  int ans=(int)1e9;
		int now=root;
		while (now){
		  if (T[now].data>x) ans=min(ans,T[now].data),now=T[now].ls;
			else now=T[now].rs;
		}
		return ans;
	}
	void insert(int x){
	  int k=findpos(x);
		par tmp=split(root,k);
		T[++cnt].data=x;
		T[cnt].key=rand();
		T[cnt].size=1;
		root=merge(tmp.first,cnt);
		root=merge(root,tmp.second);
	}
	void del(int x){
	  int k=findpos(x);
		par t1=split(root,k);
		par t2=split(t1.first,k-1);
    root=merge(t2.first,t1.second);
	}
}
int main(){
	using namespace Treap;
  int n;
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		int op,x;
	  scanf("%d%d",&op,&x);
		if (op==1) insert(x);
		else if (op==2) del(x);
		else if (op==3) printf("%d\n",findpos(x));
		else if (op==4) printf("%d\n",findx(x));
		else if (op==5) printf("%d\n",pre(x));
		else printf("%d\n",neg(x));
	}
	return 0;
}
