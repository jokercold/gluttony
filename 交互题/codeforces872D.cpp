#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int ans[5050][5050],p[5050],b[5050],p_true[5050];
int main(){
  int n;
  scanf("%d",&n);
  int x;
  for(int i=0;i<n;i++){
    printf("? %d %d\n",i,0);
    fflush(stdout);
    scanf("%d",&x);
    ans[i][0]=x;
  }
  for(int i=1;i<n;i++){
    printf("? %d %d\n",0,i);
    fflush(stdout);
    scanf("%d",&x);;
    ans[0][i]=x;
  }
  int yh=0;
  for(int i=0;i<n;i++){
    memset(p,-1,sizeof(p));
    memset(b,-1,sizeof(b));
    p[0]=i;
    for (int j=0;j<n;++j)
      b[j]=ans[0][j]^p[0];
    for (int j=1;j<n;++j)
      p[j]=ans[j][0]^b[0];
    bool flag=true;
		for (int j=0;j<n;++j)
		if (p[b[j]]!=j||p[j]>=n||b[j]>=n){
		  flag=false;
		  break;
		} 
		if (flag){
			yh++;
			for (int j=0;j<n;++j) p_true[j]=p[j];
		}
  }
  printf("!\n");
  printf("%d\n",yh);
  for(int i=0;i<n;i++) printf("%d ",p_true[i]);
  printf("\n");
  fflush(stdout);
  return 0;
}

