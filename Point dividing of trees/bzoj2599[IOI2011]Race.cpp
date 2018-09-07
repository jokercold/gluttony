#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int num,K,ans;
#define N 200005
int hash[1005000];
int to[N+N],hed[N],Next[N+N],val[N+N];
int deep[N],edge[N],size[N];
bool flag[N];
void add(int u,int v,int z){
  ++num;
  to[num]=v;
  val[num]=z;
  Next[num]=hed[u];
  hed[u]=num;
}
void getsize(int u,int fa){
  size[u]=1;
  for (int i=hed[u];i;i=Next[i])
  if (to[i]!=fa&&flag[to[i]]){
    getsize(to[i],u);
    size[u]+=size[to[i]];
  }
}
int getroot(int u,int fa,int ma){
  for (int i=hed[u];i;i=Next[i])
  if (to[i]!=fa&&flag[to[i]]&&size[to[i]]+size[to[i]]>ma) return getroot(to[i],u,ma);
  return u;
}
void getdeep(int u,int fa){
  if (deep[u]<=K) ans=min(ans,edge[u]+hash[K-deep[u]]);
	for (int i=hed[u];i;i=Next[i])
	if (to[i]!=fa&&flag[to[i]]){
		edge[to[i]]=edge[u]+1;
		deep[to[i]]=deep[u]+val[i];
		getdeep(to[i],u);
	}
}
void adddeep(int u,int fa,int z){
  if (deep[u]<=K){
	  if (z==1) hash[deep[u]]=min(hash[deep[u]],edge[u]);
		else hash[deep[u]]=1<<29;
	}
	for (int i=hed[u];i;i=Next[i])
	if (to[i]!=fa&&flag[to[i]]) adddeep(to[i],u,z);
}
void calc(int u){
  for (int i=hed[u];i;i=Next[i])
	if (flag[to[i]]){
	  deep[to[i]]=val[i];edge[to[i]]=1;
		getdeep(to[i],0);
		adddeep(to[i],0,1);
	}
	for (int i=hed[u];i;i=Next[i])
	if (flag[to[i]])
		adddeep(to[i],0,0);
}
void work(int u){
  flag[u]=false;
	calc(u);
  getsize(u,-1);
  for (int i=hed[u];i;i=Next[i])
  if (flag[to[i]]){
    int rt=getroot(to[i],u,size[to[i]]);
    work(rt);
  }
}
int main(){
  int n;
  scanf("%d%d",&n,&K);
	hash[0]=0;
  for (int i=1;i<=K;++i) hash[i]=1<<29;
	ans=1<<29;
  num=1;
  for (int i=1;i<=n;++i) hed[i]=0,flag[i]=true;
  for (int i=1;i<n;++i){
    int u,v,z;
    scanf("%d%d%d",&u,&v,&z);
    ++u;++v;
		add(u,v,z);
    add(v,u,z);
  }
  getsize(1,-1);
  int rt=getroot(1,-1,size[1]);
  work(rt);
	if (ans==1<<29) ans=-1;
  printf("%d\n",ans);
  return 0;
}
