#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define M 2009
int n;
struct matrix{
  int TJ[120][120];
	matrix(){memset(TJ,0,sizeof(TJ));}
  friend matrix operator *(matrix A,matrix B){
	  matrix c;
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j){
				c.TJ[i][j]=0;
				for (int k=1;k<=n;++k)
					c.TJ[i][j]=(c.TJ[i][j]+A.TJ[i][k]*B.TJ[k][j]%M)%M;
			}
	  return c;
	}
};
matrix S,ans;
char ch[30];
void power(int T){
  while (T){
		if (T&1) ans=ans*S;
		S=S*S;
	  T>>=1;
	}
}
int main(){
  int N,T;
	scanf("%d%d",&N,&T);
	n=N*9;
	for (int i=1;i<=N;++i)
		for (int j=1;j<=8;++j)
		S.TJ[(i-1)*9+j][(i-1)*9+j+1]=1;
  for (int i=1;i<=N;++i){
	  scanf("%s",ch+1);
    for (int j=1;j<=N;++j)
		if (ch[j]>'0')
			S.TJ[(i-1)*9+ch[j]-'0'][(j-1)*9+1]=1;
	}
	for (int i=1;i<=n;++i) 
		ans.TJ[i][i]=1;
	power(T);
	printf("%d\n",ans.TJ[1][(N-1)*9+1]);
	return 0;
}
