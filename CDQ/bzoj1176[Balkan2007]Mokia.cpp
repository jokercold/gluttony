#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 2005000
#define M 2005000
#define lowbit(i) ((i)&(-i))
struct node{
  int id,x,y,z;
}matrix[M],a[M],b[M];
bool cmp(node x,node y){
 return x.x<y.x;
}
int ans[M];
int hight[N];
void add(int x,int y){
  for (int i=x;i<N;i+=lowbit(i)) hight[i]+=y;
}
int sum(int x){
	int ans=0;
  for (int i=x;i>0;i-=lowbit(i)) ans+=hight[i];
	return ans;
}
void cdq(int l,int r){
  if (l>=r) return;
	int mid=(l+r)>>1;
	int h=l,t=l-1;
	for (int i=l;i<=mid;++i)
	if (matrix[i].z<=2000000){
	  ++t;
		a[t]=matrix[i];
	}
	sort(a+h,a+t+1,cmp);
	for (int i=mid+1;i<=r;++i) b[i]=matrix[i];
	sort(b+mid+1,b+r+1,cmp);
	for (int i=mid+1;i<=r;++i)
	if (b[i].z>2000000){
	  while (h<=t&&a[h].x<=b[i].x) add(a[h].y,a[h].z),++h;
    if (b[i].z==2000001||b[i].z==2000004) ans[b[i].id]+=sum(b[i].y);
		else ans[b[i].id]-=sum(b[i].y);
	}
	for (int i=l;i<h;++i) add(a[i].y,-a[i].z);
	cdq(l,mid);
	cdq(mid+1,r);
}
int main(){
  int S,n;
	scanf("%d%d",&S,&n);
	int m=0;
	int t=0;
	while (true){
		++m;
	  int q;
		scanf("%d",&q);
		if (q==3) break;
		if (q==1){
		  int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
      ++t;matrix[t].id=m;matrix[t].x=x;matrix[t].y=y;matrix[t].z=z;
			ans[m]=-1e9;
		}else{
		  int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			++t;matrix[t].id=m;matrix[t].x=x1-1;matrix[t].y=y1-1;matrix[t].z=2000001;
		  ++t;matrix[t].id=m;matrix[t].x=x1-1;matrix[t].y=y2;matrix[t].z=2000002;
      ++t;matrix[t].id=m;matrix[t].x=x2;matrix[t].y=y1-1;matrix[t].z=2000003;
		  ++t;matrix[t].id=m;matrix[t].x=x2;matrix[t].y=y2;matrix[t].z=2000004;
		  ans[m]=0;
		}
	} 
	--m;
	cdq(1,t);
	for (int i=1;i<=m;++i)
	if (ans[i]!=-1e9) printf("%d\n",ans[i]);
	return 0;
}
