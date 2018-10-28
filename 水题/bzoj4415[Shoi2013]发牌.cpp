#include<iostream>
#include<cstdio>
using namespace std;
int sp[20000000];
void build(int p,int l,int r){
	sp[p]=r-l+1;
	if (l==r) return;
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
void change(int p,int l,int r,int k){
	sp[p]--;
	if (l==r){printf("%d\n",l);return;}
	int mid=(l+r)>>1;
	if (sp[p<<1]>=k) change(p<<1,l,mid,k);
	else change(p<<1|1,mid+1,r,k-sp[p<<1]);
}
int main(){
	int n;
	scanf("%d",&n);
  build(1,1,n);
	int cnt=n;
	int now=0;
  while (cnt--){
		int x;
		scanf("%d",&x);
		now=(now+x)%(cnt+1);
		change(1,1,n,now+1);
	}
	return 0;
}
