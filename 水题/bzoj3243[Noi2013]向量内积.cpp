#include<bits/stdc++.h>
using namespace std;
inline int read(){
  char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	return tmp;
}
int ss[5];
int b[105],c[105][105],a[100005][105],r[100005];
int n,m,p;
int haha(int i){
  int yh=0;
	if (p==2)
		for (int j=1;j<=m;++j)
      yh+=b[j]*a[i][j],b[j]+=a[i][j];
	else 
		for (int j=1;j<=m;++j)
			for (int k=1;k<=m;++k){
			  yh+=c[j][k]*a[i][j]*a[i][k];
				c[j][k]+=a[i][j]*a[i][k];
			}
	return yh%p;
}
void check(int i,int j){
  if (i==0) cout<<"!"<<endl;
	int yh=0;
	for (int k=1;k<=m;++k)
		yh+=a[i][k]*a[j][k];
	if (yh%p==0){
	  if (i>j) swap(i,j);
		printf("%d %d\n",i,j);
	  exit(0);
	}
}
int main(){
	n=read();m=read();p=read();
	for (int i=1;i<=n;++i)
	  for (int j=1;j<=m;++j) a[i][j]=read()%p;
  for (int i=1;i<=n;++i) r[i]=i;
	srand(233);
  random_shuffle(r+1,r+n+1);
  for (int i=1;i<=n;++i)
	if (haha(r[i])!=(i-1)%p)
		for (int j=1;;check(r[i],r[j++]));
	for (int i=1;i<=m;++i) b[i]=0;
	for (int i=1;i<=m;++i) for (int j=1;j<=m;++j) c[i][j]=0;
	for (int i=1;i<=n;++i) r[i]=i;
	srand(611);
  for (int i=1;i<=n;++i)
	if (haha(r[i])!=(i-1)%p)
		for (int j=1;;check(r[i],r[j++]));
	puts("-1 -1");
	return 0;
}
