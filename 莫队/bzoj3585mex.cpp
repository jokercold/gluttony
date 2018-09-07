#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define N 300000
int a[N],belong[N],ans[N],c[N];
struct node{
  int l,r,id;
}q[N];
bool cmp(node x,node y){
  return belong[x.l]==belong[y.l]?(belong[x.r]==belong[y.r]?x.id<y.id:belong[x.r]<belong[y.r]):belong[x.l]<belong[y.l];
}
int Ans,n,m;
void Update(int x){
	if (x>n)return; 
  c[x]++;
	if (c[x]==0&&x<Ans) Ans=x;
	if (Ans==x) while (c[Ans]) Ans++;
}
void Delete(int x){
	if (x>n)return;
  c[x]--;
	if (c[x]==0&&x<Ans) Ans=x;
}
void modui(){
  int l=1,r=0;
	for (int i=1;i<=m;++i){
	  while (l<q[i].l) Delete(a[l]),++l;
	  while (l>q[i].l) Update(a[l-1]),--l;
		while (r<q[i].r) Update(a[r+1]),++r;
    while (r>q[i].r) Delete(a[r]),r--;
	  ans[q[i].id]=Ans;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	int block=sqrt(n);
	for (int i=1;i<=n;++i) belong[i]=(i-1)/block+1;
	for (int i=1;i<=m;++i){
	  scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	Ans=0;
	modui();
	for (int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
