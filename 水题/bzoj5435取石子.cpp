#include<iostream>
#include<cstdio>
using namespace std;
int a[50010];
bool check(int L,int R){
	int l=L,r=R;
	while (l<r&&a[l]==a[r]) l++,r--;
	for (int i=l;i<=r;i+=2) if (a[i]^a[i+1]) return 0;
	int cnt=0;
	for (int i=L;i<=R;i++) cnt+=a[i];
	return cnt/2%2==0;
}
int solve(){
	int n;
	scanf("%d",&n);
	int sum=0;
	for (int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		sum^=a[i];
	}
	if (!sum) return 0;
	if (n%2==0) return 1;
	int k=30;
	for (k=30;!(sum>>k&1);k--);
	for (int i=1;i<=n;++i) a[i]=a[i]>>k&1;
	if (!a[1]&&!a[n]) return -1;
	if (a[1]&&check(2,n)) return 1;
	if (a[n]&&check(1,n-1)) return 1;
	return -1;
}
int main(){
	int cas;
	scanf("%d",&cas);
	while (cas--){
		int t=solve();
		if (t==1) printf("Alice\n");
		if (t==0) printf("Draw\n");
		if (t==-1) printf("Bob\n");
	}
	return 0;
}
