#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int num,t,K,ans;
#define N 50005
int to[N+N],head[N],Next[N+N],val[N+N];
int a[N],deep[N],size[N];
bool flag[N];
void add(int u,int v,int z){
  ++num;
  to[num]=v;
  val[num]=z;
  Next[num]=head[u];
  head[u]=num;
}
void getsize(int u,int fa){
  size[u]=1;
  for (int i=head[u];i;i=Next[i])
  if (to[i]!=fa&&flag[to[i]]){
    getsize(to[i],u);
    size[u]+=size[to[i]];
  }
}//预处理size
int getroot(int u,int fa,int ma){
  for (int i=head[u];i;i=Next[i])
  if (to[i]!=fa&&flag[to[i]]&&size[to[i]]+size[to[i]]>ma) return getroot(to[i],u,ma);
  return u;
}//找重心
void getdeep(int u,int fa){
  a[t++]=deep[u];
  for (int i=head[u];i;i=Next[i])
  if (to[i]!=fa&&flag[to[i]]) deep[to[i]]=deep[u]+val[i],getdeep(to[i],u);
}
int calc(int u,int ss){
  t=0;
  deep[u]=ss;
  getdeep(u,-1);
  sort(a,a+t);
  int l=0,r=t-1,xx=0;
  while (l<r){
    if (a[l]+a[r]>K){--r;continue;}
    xx+=r-l;
    ++l;
  }
  return xx; 
}
void work(int u){
  flag[u]=false;
  getsize(u,-1);
  ans+=calc(u,0);
  for (int i=head[u];i;i=Next[i])
  if (flag[to[i]]){
    ans-=calc(to[i],val[i]);
    int rt=getroot(to[i],u,size[to[i]]);
    work(rt);
  }
}
int main(){
  int n;
  scanf("%d",&n);
  ans=0;
  num=0;
  for (int i=1;i<=n;++i) head[i]=0,flag[i]=true;
  for (int i=1;i<n;++i){
    int u,v,z;
    scanf("%d%d%d",&u,&v,&z);
    add(u,v,z);
    add(v,u,z);
  }
	scanf("%d",&K);
  getsize(1,-1);
  int rt=getroot(1,-1,size[1]);
  work(rt);
  printf("%d\n",ans);
  return 0;
}
