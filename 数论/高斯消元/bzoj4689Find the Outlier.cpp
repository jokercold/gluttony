#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define db double
#define N 10
#define eps 1e-3
db f[N],s[N][N],ans[N];
int n,m;
void Guess(){
	for (int i=2;i<=m;++i){
	  for (int j=i;j<=m;++j){
		  db zz=s[j][i-1]/s[i-1][i-1];
			for (int k=i;k<=m+1;++k)
				s[j][k]=zz*s[i-1][k]-s[j][k];
		}
	}
	for (int i=m;i>=1;i--){
	  ans[i]=s[i][m+1];
		for (int j=i+1;j<=m;++j)
			ans[i]=ans[i]-ans[j]*s[i][j];
		ans[i]=ans[i]/s[i][i];
	}
}
bool check(int x){
  m=0;
	for (int i=0;i<=n+2;++i)
  if (i!=x){
	  ++m;
		s[m][1]=1;
		for (int j=2;j<=n+1;++j)
			s[m][j]=s[m][j-1]*i;
		s[m][n+2]=f[i];
    if (m==n+1) break;
	}
	Guess();
	for (int i=n+2;i>=0;i--)
	if (i!=x){
		db num=0;
		db S=1;
		for (int j=1;j<=n+1;++j)
      num=num+ans[j]*S,S=S*i;
		if (abs(num-f[i])<=eps) return true;
    else return false;
	}
}
int main(){
	while (true){
		scanf("%d",&n);
		if (n==0) break;
		for (int i=0;i<=n+2;++i) scanf("%lf",&f[i]);
		for (int i=0;i<=n+2;++i)
		if (check(i)){
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}
