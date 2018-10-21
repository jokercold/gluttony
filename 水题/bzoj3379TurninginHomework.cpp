#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int x,t;
}a[2000];
int f[1010][1010][2];
bool cmp(node x,node y){
	if (x.x!=y.x) return x.x<y.x;
	else return x.t<y.t;
}
int main(){
	int C,H,B;
	scanf("%d%d%d",&C,&H,&B);
	for (int i=1;i<=C;++i) scanf("%d%d",&a[i].x,&a[i].t);
	sort(a+1,a+C+1,cmp);
	for (int i=0;i<=C+1;++i)
		for (int j=0;j<=C+1;++j)
			f[i][j][0]=f[i][j][1]=1<<29;
	f[1][C][0]=max(a[1].x,a[1].t);
	f[1][C][1]=max(a[C].x,a[C].t);
	for (int len=C-1;len>=0;--len)
		for (int i=1;i<=C-len;++i){
			int j=i+len;
      f[i][j][0]=min(f[i][j][0],min(max(f[i-1][j][0]+a[i].x-a[i-1].x,a[i].t),max(f[i][j+1][1]+a[j+1].x-a[i].x,a[i].t)));
      f[i][j][1]=min(f[i][j][1],min(max(f[i-1][j][0]+a[j].x-a[i-1].x,a[j].t),max(f[i][j+1][1]+a[j+1].x-a[j].x,a[j].t)));
		}
	int ans=1<<29;
	for (int i=1;i<=C;++i)
		ans=min(ans,min(f[i][i][0],f[i][i][1])+(B>a[i].x?B-a[i].x:a[i].x-B));
	printf("%d\n",ans);	
	return 0;
}
