#include<iostream>
#include<cstdio>
using namespace std;
#define N 50001
int size,rt;
namespace splay{
  int tr[N][2],fa[N],num[N];
  void rotate(int x,int &k){
    int y=fa[x],z=fa[y],l,r;
    if (tr[y][0]==x) l=0;else l=1;
    r=1-l;
    if (y==k) k=x;
    else tr[z][tr[z][1]==y]=x;
    fa[x]=z;fa[y]=x;fa[tr[x][r]]=y;
    tr[y][l]=tr[x][r];tr[x][r]=y;
  }
  void splay(int x,int &k){
    while (x!=k){
      int y=fa[x],z=fa[y];
      if (y!=k){
        if ((tr[y][0]==x)^(tr[z][0]==y)) rotate(x,k);
				else rotate(y,k);
      }
      rotate(x,k);
    }
  }
  void insert(int &k,int x,int last){
    if (k==0){++size;k=size;num[k]=x;fa[k]=last;splay(k,rt);return;}
    if (x<num[k]) insert(tr[k][0],x,k);
    else insert(tr[k][1],x,k);
  }
  void before(int k,int x,int &t){
    if (k==0) return;
    if (num[k]<=x){t=num[k];before(tr[k][1],x,t);}
    else before(tr[k][0],x,t);
  }
  int Before(int k,int x){
    int t=-1<<29;
    before(k,x,t);
    return t;
  } 
  void after(int k,int x,int &t){
 		if (k==0) return;
		if (num[k]>=x){t=num[k];after(tr[k][0],x,t);}
		else after(tr[k][1],x,t);
  }
	int After(int k,int x){
	  int t=1<<29;
		after(k,x,t);
		return t;
	}
}
int main(){
  int n;
	scanf("%d",&n);
	int cas=0,ans=0;
	rt=size=0;
	while (n--){
	  ++cas;
		int x;
		scanf("%d",&x);
    int t1=splay::Before(rt,x);
		int t2=splay::After(rt,x);
	  if (cas!=1) ans+=min(x-t1,t2-x);
		else ans+=x;
		//cout<<size<<endl;
    //cout<<t1<<" "<<x<<" "<<t2<<endl;
		splay::insert(rt,x,0);
	}
  printf("%d\n",ans);
	return 0;
}
