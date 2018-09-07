#include<set>
#include<map>
#include<queue>
#include<ctime>
#include<cmath>
#include<cstdio>
#include<vector>
#include<string>
#include<cctype>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<utility>
#include<iostream>
#include<algorithm>
#define REP(i,a,b) for(int i=(a);i<=(b);i++)
#define PER(i,a,b) for(int i=(a);i>=(b);i--)
#define RVC(i,S) for(int i=0;i<(S).size();i++)
#define RAL(i,u) for(int i=fr[u];i!=-1;i=e[i].next)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
     
template<class T> inline
void read(T& num){
  bool start=false,neg=false;
  char c;
  num=0;
  while((c=getchar())!=EOF){
    if(c=='-') start=neg=true;
    else if(c>='0'&&c<='9'){
      start=true;
      num=num*10+c-'0';
    }else if(start) break;
  }
  if(neg) num=-num;
}
/*============ Header Template ============*/

struct edge{
  int next,to;
};

const int maxn=(int)(2e5)+5;
int fr[maxn];
int ai[maxn];
int mx[maxn];
int su[maxn];
int dep[maxn];
int ls[maxn*75],rs[maxn*75],sum[maxn*75],mi[maxn*75];
edge e[maxn];
int idx,tote,n,m;

inline void addedge(int u,int v){
  ++tote;
  e[tote].next=fr[u];fr[u]=tote;e[tote].to=v;
}

inline int newnode(){
  return ++idx;
}

void add(int& x,int l,int r,int p,int v){
  int px=x;
  x=newnode();
  ls[x]=ls[px];rs[x]=rs[px];
  sum[x]=sum[px]+v;
  if(l==r) return;
  int mid=(l+r)>>1;
  if(p<=mid) add(ls[x],l,mid,p,v);
  else add(rs[x],mid+1,r,p,v);
}

void mergeS(int& x,int xi,int yi,int l,int r){
  if(!xi && !yi){
    x=0;
    return;
  }
  x=newnode();
  if(!xi){
    ls[x]=ls[yi];rs[x]=rs[yi];
    sum[x]=sum[yi];return;
  }
  if(!yi){
    ls[x]=ls[xi];rs[x]=rs[xi];
    sum[x]=sum[xi];return;
  } 
  sum[x]=sum[xi]+sum[yi];
  if(l==r) return;
  int mid=(l+r)>>1;
  mergeS(ls[x],ls[xi],ls[yi],l,mid);
  mergeS(rs[x],rs[xi],rs[yi],mid+1,r);
}
int now;
void mergeM(int& x,int xi,int yi,int l,int r){
  if(!xi && !yi){
    x=0;
		return;
	}
	x=newnode();
	if(!xi){
		ls[x]=ls[yi];rs[x]=rs[yi];
		mi[x]=mi[yi];return;
	}
	if(!yi){
		ls[x]=ls[xi];rs[x]=rs[xi];
		mi[x]=mi[xi];return;
	}
	if(l==r){
		if(!mi[yi]) mi[x]=mi[xi];
		else if(!mi[xi]) mi[x]=mi[yi];
		else if(mi[xi]<mi[yi]){
			add(su[now],1,n,mi[yi],-1);
			mi[x]=mi[xi];
		}else{
			add(su[now],1,n,mi[xi],-1);
			mi[x]=mi[yi];
		} 
 		return;
	}
	int mid=(l+r)>>1;
	mergeM(ls[x],ls[xi],ls[yi],l,mid);
	mergeM(rs[x],rs[xi],rs[yi],mid+1,r);
}

inline int qsum(int x,int k){
  int l=1,r=n,res=0;
  while(l<r){
    int mid=(l+r)>>1;
    if(k<=mid) x=ls[x],r=mid;
    else res+=sum[ls[x]],x=rs[x],l=mid+1;
  }
  return res+sum[x];
}

void upd(int& x,int l,int r,int p,int v){
  int px=x;
  x=newnode();
  ls[x]=ls[px];rs[x]=rs[px];mi[x]=mi[px];
  if(l==r){
    if(!mi[x]) mi[x]=v;
    else if(v<mi[x]) {
      add(su[now],1,n,mi[x],-1);
      mi[x]=v;
    } 
		return;
  }
  int mid=(l+r)>>1;
  if(p<=mid) upd(ls[x],l,mid,p,v);
  else upd(rs[x],mid+1,r,p,v);
}

void dfs(int x){
  add(su[x],1,n,dep[x],1);
  upd(mx[x],1,n,ai[x],dep[x]);
  RAL(i,x){
    dep[e[i].to]=dep[x]+1;
    dfs(e[i].to);
    now=x;int nsu=0,nmx=0;
    mergeS(nsu,su[x],su[e[i].to],1,n);su[x]=nsu;
    mergeM(nmx,mx[x],mx[e[i].to],1,n);mx[x]=nmx;
  }
}

void solve(){
  read(n);read(m);idx=tote=0;
  REP(i,1,n) read(ai[i]);
  REP(i,1,n) mx[i]=su[i]=0,fr[i]=-1;
  REP(i,2,n){
   int f;read(f);addedge(f,i);
  } 
  dep[1]=1;dfs(1);
  int lst=0; 
  REP(i,1,m){
    int x,v;
    read(x);read(v);
    x^=lst;v^=lst;
    lst=qsum(su[x],min(n,dep[x]+v));
    printf("%d\n",lst);
  }
}

int main(){
  int T;
  read(T);
  while(T--) solve();
  return 0;
}
