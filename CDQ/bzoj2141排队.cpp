#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 100050
#define lowbit(x) ((x)&(-x))
inline int read(){
  char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	int tmp=0;
	while (ch>='0'&&ch<='9')tmp=tmp*10+ch-'0',ch=getchar();
	return tmp;
}
int n;
int ans[N],a[N],mp[N];
struct node{
  int t,x,y,type,id;
}q[N],t[N];
int h[N];
inline void add(int x,int v){
  for (int i=x;i<=n;i+=lowbit(i)) h[i]+=v;
}
inline int sum(int x){
  int ans=0;
	for (int i=x;i>0;i-=lowbit(i)) ans+=h[i];
	return ans;
}
void CDQ(int l,int r){
  if (l==r) return;
	int mid=(l+r)>>1;
	for (int i=l;i<=r;++i)
	if (q[i].t<=mid) add(q[i].y,q[i].type);
	else ans[q[i].id]+=q[i].type*(sum(n)-sum(q[i].y));
  for (int i=l;i<=r;++i) if (q[i].t<=mid) add(q[i].y,-q[i].type);
	for (int i=r;i>=l;--i)
	if (q[i].t<=mid) add(q[i].y,q[i].type);
	else ans[q[i].id]+=q[i].type*sum(q[i].y-1);
	for (int i=l;i<=r;++i) if (q[i].t<=mid) add(q[i].y,-q[i].type);
	int p1=l,p2=mid+1;
	for (int i=l;i<=r;++i)
	if (q[i].t<=mid) t[p1++]=q[i];
	else t[p2++]=q[i];
	for (int i=l;i<=r;++i) q[i]=t[i];
  CDQ(l,mid);
	CDQ(mid+1,r);
}
bool cmp(node x,node y){
  if (x.x!=y.x) return x.x<y.x;
	else return x.y<y.y;
}
int main(){
  n=read();
	for (int i=1;i<=n;++i) a[i]=mp[i]=read();
  sort(mp+1,mp+1+n); mp[0]=unique(mp+1,mp+1+n)-mp-1;
	int tim=0;
	int m=0;
	for (int i=1;i<=n;++i)
		a[i]=lower_bound(mp+1,mp+1+mp[0],a[i])-mp,q[++m]=(node){++tim,i,a[i],1,0};
	n=mp[0];
	int Q=read();
  for (int i=1;i<=Q;++i){
	  int p1=read(),p2=read();
		q[++m]=(node){++tim,p1,a[p2],1,i};q[++m]=(node){++tim,p2,a[p1],1,i};
		q[++m]=(node){++tim,p1,a[p1],-1,i};q[++m]=(node){++tim,p2,a[p2],-1,i};
		swap(a[p1],a[p2]);
	}	
	sort(q+1,q+m+1,cmp);
	CDQ(1,m);
	printf("%d\n",ans[0]);
	for (int i=1;i<=Q;++i) ans[i]+=ans[i-1],printf("%d\n",ans[i]);
	return 0;
}
