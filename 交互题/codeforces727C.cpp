#include<iostream>
#include<cstdio>
using namespace std;
int S[6000],X[6000];
inline int get(int i,int j){
  printf("? %d %d\n",i,j);
  fflush(stdout);
  int x;
  scanf("%d",&x);
  return x;
}
int main(){
  int n;
  scanf("%d",&n);
  for (int i=1;i<n;++i) S[i]=get(i,i+1);
  S[0]=get(1,3);
  X[2]=(S[1]+S[2]-S[0])>>1;
  X[1]=S[1]-X[2];
  for (int i=2;i<n;++i)
    X[i+1]=S[i]-X[i];
  printf("!");
  for (int i=1;i<=n;++i)
    printf(" %d",X[i]);
  printf("\n");
  fflush(stdout);
  return 0;
}
