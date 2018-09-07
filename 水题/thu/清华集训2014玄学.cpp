#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
inline int read(){
  char last='+',ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-')last='-';ch=getchar();}
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
  if (last=='-') tmp=-tmp;
	return tmp;
}
#define ll long long
ll A,B;
int q,L,R,K,a,b,n,m;
struct node{
  int pos;
	ll a,b;
	friend bool operator <(node x,node y){
	  return x.pos<y.pos;
	}
};
#define N 600100
vector<node> vec[N*4];
ll val[N];
void update(int p){
  int ls=p<<1,rs=p<<1|1;
	vector<node>::iterator lit=vec[ls].begin(),rit=vec[rs].begin(),lend=vec[ls].end()-1,rend=vec[rs].end()-1;
  while (true){
	  vec[p].push_back((node){max((*lit).pos,(*rit).pos),(*lit).a*(*rit).a%m,(((*lit).b*(*rit).a%m)+(*rit).b)%m});
		if (lit==lend&&rit==rend) break;
		if (lit==lend) ++rit;
		else if (rit==rend) ++lit;
		else if ((*(lit+1)).pos>(*(rit+1)).pos) rit++;
		else if ((*(lit+1)).pos<(*(rit+1)).pos) lit++;
		else lit++,rit++;
	}
}
void change(int p,int l,int r,int x){
  if (l==r){
	  if (L!=1) vec[p].push_back((node){1,1,0});
	  vec[p].push_back((node){L,a,b});
		if (R!=n) vec[p].push_back((node){R+1,1,0});
	  return;
	}
  int mid=(l+r)>>1;
	if (mid>=x) change(p<<1,l,mid,x);
	else change(p<<1|1,mid+1,r,x);
	if (x==r) update(p);
}
void query(int p,int l,int r){
	if (l>R||r<L) return;
	if (L<=l&&r<=R){
	  vector<node>::iterator it=upper_bound(vec[p].begin(),vec[p].end(),(node){K,0,0})-1;
		A=A*(*it).a%m;
		B=(B*(*it).a%m+(*it).b)%m;
		return;
	}
	int mid=(l+r)>>1;
	query(p<<1,l,mid);
	query(p<<1|1,mid+1,r);
}
int main(){
  int TJJ;
	TJJ=read();
  n=read();m=read();
  for (int i=1;i<=n;++i) val[i]=read();
	q=read();
	ll lastans=0;
	int num=0;
	for (int i=1;i<=q;++i){
	  int cmd;
		cmd=read();
    if (cmd==1){
		  L=read(),R=read(),a=read(),b=read();
			if (TJJ&1)L^=lastans,R^=lastans;
			++num;
			change(1,1,q,num);
		}else{
		  L=read(),R=read();
			K=read();
			A=1,B=0;
		  if (TJJ&1){L^=lastans;R^=lastans;K^=lastans;}
			query(1,1,q);
			lastans=((val[K]*A%m)+B)%m;
			printf("%lld\n",lastans);
		}
	}
	return 0;
}
