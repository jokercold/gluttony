#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
	char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	return tmp;
}
#define ll long long
#define N 300000
#define M 10000005
int n,m,k,q,Tx,Ty;
int ccx[N],ccy[N],root[N];
struct node{
  int x,y,s;
}Q[N];
bool cmp(node x,node y){
	return x.x<y.x;
}
struct yh{
  ll a1,a2,a3,a4;
	yh(){a1=a2=a3=a4=0;}
  friend yh operator +(yh x,yh y){
	  yh ans;
		ans.a1=x.a1+y.a1;
		ans.a2=x.a2+y.a2;
		ans.a3=x.a3+y.a3;
		ans.a4=x.a4+y.a4;
		return ans;
	}
}tree[M];
int ls[M],rs[M];
int siz;
void add(int &y,int l,int r,int xx,int qx,int qy,ll z){
  ++siz;
	ls[siz]=ls[y];
	rs[siz]=rs[y];
	tree[siz]=tree[y];
	y=siz;
	if (l==r){
	  tree[y].a1+=z;
		tree[y].a2+=z*(qy-1);
		tree[y].a3+=z*(qx-1);
		tree[y].a4+=z*(qx-1)*(qy-1);
		return;
	}
	int mid=(l+r)>>1;
	if (xx<=mid) add(ls[y],l,mid,xx,qx,qy,z);
	else add(rs[y],mid+1,r,xx,qx,qy,z);
	tree[y]=tree[ls[y]]+tree[rs[y]];
}
yh query(int rt,int l,int r,int x){
  yh ans;
	if (!rt) return ans;
	if (l==r) return tree[rt];
	int mid=(l+r)>>1;
	if (x<=mid) return query(ls[rt],l,mid,x);
	else return tree[ls[rt]]+query(rs[rt],mid+1,r,x);
}
ll Q_Q(int x,int y){
	int xx=upper_bound(ccx+1,ccx+Tx+1,x)-ccx-1;
	int yy=upper_bound(ccy+1,ccy+Ty+1,y)-ccy-1;
  if (xx==0||yy==0) return 0;
	yh ret=query(root[xx],1,Ty,yy);
	//cout<<ret.a1<<" "<<ret.a2<<" "<<ret.a3<<" "<<ret.a4<<endl;
  return ret.a1*x*y+ret.a4-ret.a2*x-ret.a3*y;
}
int main(){
	n=read();m=read();k=read();q=read();
	int num=0;
	Tx=0,Ty=0;
	for (int i=1;i<=k;++i){
	  int x1=read(),x2=read(),y1=read(),y2=read(),s=read();
    Q[++num]=(node){x1,y1,s};Q[++num]=(node){x1,y2+1,-s};
	  Q[++num]=(node){x2+1,y1,-s};Q[++num]=(node){x2+1,y2+1,s};
	  ccx[++Tx]=x1;ccx[++Tx]=x2+1;
		ccy[++Ty]=y1;ccy[++Ty]=y2+1;
	}
	sort(ccx+1,ccx+Tx+1);
	sort(ccy+1,ccy+Ty+1);
	Tx=unique(ccx+1,ccx+Tx+1)-ccx-1;
	Ty=unique(ccy+1,ccy+Ty+1)-ccy-1;
	sort(Q+1,Q+num+1,cmp);
	int ti=0;
  int tj=1;
  while (tj<=num){
		++ti;
		root[ti]=root[ti-1];
 	  int dx=Q[tj].x;
		while (tj<=num&&Q[tj].x==dx){
		  add(root[ti],1,Ty,lower_bound(ccy+1,ccy+Ty+1,Q[tj].y)-ccy,Q[tj].x,Q[tj].y,Q[tj].s);
			++tj;
		}
	}
	ll lastans=0;
  while (q--){
		int x=read(),y=read();
	  int x1=lastans%n+1,x2=(lastans+x)%n+1;
		int y1=lastans%m+1,y2=(lastans+y)%m+1;
		if (x1>x2) swap(x1,x2);
		if (y1>y2) swap(y1,y2);
		x1=max(1,x1);
		y1=max(1,y1);
		x2=min(n,x2);
		y2=min(m,y2);
	  //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
		printf("%lld\n",lastans=(Q_Q(x2,y2)+Q_Q(x1-1,y1-1)-Q_Q(x1-1,y2)-Q_Q(x2,y1-1)));
	} 
	return 0;
}

