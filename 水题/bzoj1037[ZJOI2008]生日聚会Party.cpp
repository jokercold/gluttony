#include<iostream>
#include<cstdio>
using namespace std;
#define M 12345678
int f[400][160][22][22];
int main(){
  int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	f[0][0][0][0]=1;
	for (int i=0;i<n+m;++i)
		for (int j=0;j<=n;++j)
			for (int x=0;x<=k;++x)
				for (int y=0;y<=k;++y)
				if (f[i][j][x][y]){
					if (j+1<=n&&x+1<=k) (f[i+1][j+1][x+1][max(y-1,0)]+=f[i][j][x][y])%=M;
					if (i+1-j<=m&&y+1<=k) (f[i+1][j][max(x-1,0)][y+1]+=f[i][j][x][y])%=M;
				}
	int ans=0;
	for (int x=0;x<=k;++x)
		for (int y=0;y<=k;++y) (ans+=f[n+m][n][x][y])%=M;
	printf("%d\n",ans);
	return 0;
}
