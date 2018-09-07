#include<iostream>
#include<cstdio>
using namespace std;
int dp[50];
int main(){
  int n;
	scanf("%d",&n);
	int ans=0;
	for (int i=1;i<=n;++i){
	  int x;
		scanf("%d",&x);
		int tmp=0;
		for (int j=0;j<=30;++j)
		if (x&(1<<j)) tmp=max(tmp,dp[j]);
		tmp++;
		for (int j=0;j<=30;++j)
		if (x&(1<<j)) dp[j]=max(dp[j],tmp);
		ans=max(ans,tmp);
	}
	printf("%d\n",ans);
	return 0;
}
