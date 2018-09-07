#include<iostream>
#include<cstdio>
using namespace std;
#define N 20000
int f[N];
bool vis[N];
int find(int x){
  if (f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
int main(){
  int n;
	scanf("%d",&n);
	for (int i=1;i<=10000;++i) f[i]=i;
	for (int i=1;i<=n;++i){
	  int x,y;
		scanf("%d%d",&x,&y);
		int rootx=find(x);
		int rooty=find(y);
		if (rootx==rooty) vis[rootx]=1;
		else{
		  if (rootx<rooty) swap(rootx,rooty);
			vis[rooty]=1;
			f[rooty]=rootx;
		}
	}
	for (int i=1;i<=10001;++i)
	if (!vis[i]){
	  printf("%d\n",i-1);
		break;
	}
	return 0;
}
