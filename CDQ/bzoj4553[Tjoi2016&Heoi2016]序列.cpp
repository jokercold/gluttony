#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 100300
#define lowbit(x) ((x)&(-x))
struct node{
  int x,id;	
}a[N],ma[N],mi[N],c[N],d[N];
int f[N];
bool cmp(node x,node y){
  return x.x<y.x;	
}
int h[N];
void add(int x,int y){
  //cout<<"YES"<<endl;
	//cout<<x<<" "<<y<<endl;
	for (int i=x;i<=100000;i+=lowbit(i)) h[i]=max(h[i],y);
	//cout<<"NO"<<endl;
}
int getma(int x){
  int ans=0;
	for (int i=x;i>0;i-=lowbit(i)) ans=max(ans,h[i]);
	return ans;
}
void cle(int x){
  //cout<<"YES"<<endl;
  for (int i=x;i<=100000;i+=lowbit(i)) h[i]=0;
  //cout<<"YES"<<endl;
}
int n,m;
void cdq(int l,int r){
	/*cout<<l<<" "<<r<<endl;
	for (int i=1;i<=n;++i)
		printf("%d%c",f[i]," \n"[i==n]);*/
  if (l==r){
	  f[l]=max(f[l],1);
		return;
	}
	int mid=(l+r)>>1;
  cdq(l,mid);
	for (int i=l;i<=mid;++i) c[i]=a[i];
	sort(c+l,c+mid+1,cmp);
	for (int i=mid+1;i<=r;++i) d[i]=mi[i];
	sort(d+mid+1,d+r+1,cmp);
	int h=l;
	for (int i=mid+1;i<=r;++i){
	  while (h<=mid&&c[h].x<=d[i].x){
			//cout<<h<<" "<<c[h].id<<endl;
			add(ma[c[h].id].x,f[c[h].id]);
			++h;
		}
		f[d[i].id]=max(f[d[i].id],getma(a[d[i].id].x)+1);
	}
  for (int i=l;i<=mid;++i) cle(ma[c[i].id].x);  	
  cdq(mid+1,r);
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i){
		scanf("%d",&a[i].x);
		ma[i].id=mi[i].id=a[i].id=i;
	  ma[i].x=mi[i].x=a[i].x;
	}
	for (int i=1;i<=m;++i){
	  int x,y;
		scanf("%d%d",&x,&y);
		ma[x].x=max(ma[x].x,y);
		mi[x].x=min(mi[x].x,y);
	}
	/*cout<<"YES"<<endl;*/
	cdq(1,n);
	int ans=0;
	for (int i=1;i<=n;++i) ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
