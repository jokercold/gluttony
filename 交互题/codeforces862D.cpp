#include<iostream>
#include<cstdio>
using namespace std;
int n,num1;
bool check(int l,int r){
	printf("? ");
  for (int i=0;i<l;++i) printf("0");
	for (int i=l;i<=r;++i) printf("1");
	for (int i=r+1;i<n;++i) printf("0");
	printf("\n");
	fflush(stdout);
	int now;
	cin>>now;
	if (now-num1>-(r-l+1)&&now-num1<(r-l+1)) return true;
	return false;
}
int main(){
  scanf("%d",&n);
	printf("? ");
	for (int i=0;i<n;i++) printf("0");
	printf("\n");
	fflush(stdout);
	cin>>num1;
	int L=0,R=n-1;
	while (R-L>1){
	  int mid=(R+L)>>1;
    if (check(L,mid)) R=mid;
		else L=mid;
	}
  printf("? ");
	for (int i=0;i<L;++i) printf("0");
	printf("1");
	for (int j=L+1;j<n;++j) printf("0");
	printf("\n");
	fflush(stdout);
	int now;
	cin>>now;
	printf("! ");
	if (now>num1)
	  cout<<L+1<<" "<<R+1<<endl;
	else cout<<R+1<<" "<<L+1<<endl;
	fflush(stdout);
	return 0;
}
