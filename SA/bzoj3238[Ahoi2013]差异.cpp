#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define ll long long
int n;
#define N 501000
char s[N];
int cnta[N],cntb[N],sa[N],tsa[N],rank[N<<1],height[N],a[N],b[N];
int siz[N],fa[N],pos[N];
void Get_SA(){
  for (int i=0;i<=256;++i) cnta[i]=0;
	for (int i=1;i<=n;++i) cnta[s[i]]++;
	for (int i=1;i<=256;++i) cnta[i]+=cnta[i-1];
	for (int i=n;i>=1;--i) sa[cnta[s[i]]--]=i;
	rank[sa[1]]=1;
	for (int i=2;i<=n;++i) rank[sa[i]]=rank[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
	for (int i=1;rank[sa[n]]!=n;i<<=1){
	  for (int j=1;j<=n;++j) a[j]=rank[j],b[j]=rank[j+i];
		for (int j=1;j<=n;++j) cnta[j]=cntb[j]=0;
		for (int j=1;j<=n;++j) cnta[a[j]]++,cntb[b[j]]++;
		for (int j=1;j<=n;++j) cnta[j]+=cnta[j-1],cntb[j]+=cntb[j-1];
		for (int j=n;j>=1;--j) tsa[cntb[b[j]]--]=j;
		for (int j=n;j>=1;--j) sa[cnta[a[tsa[j]]]--]=tsa[j];
		rank[sa[1]]=1;
		for (int j=2;j<=n;++j) rank[sa[j]]=rank[sa[j-1]]+(a[sa[j]]!=a[sa[j-1]]||b[sa[j]]!=b[sa[j-1]]);
	}
}
void Get_Height(){
  int len=0;
	for (int i=1;i<=n;++i){
	  if (len) len--;
    while (s[i+len]==s[sa[rank[i]-1]+len]) ++len;
		height[rank[i]]=len;
	}
}
bool cmp(int x,int y){
  return height[x]>height[y];
}
int find(int x){
  return (fa[x]==x)?x:fa[x]=find(fa[x]);
}
int main(){
  scanf("%s",s+1);
	n=strlen(s+1);
	Get_SA();
	Get_Height();
	for (int i=1;i<=n;++i){
	  fa[i]=i;
		pos[i]=i+1;
		siz[i]=1;
	}
	sort(pos+1,pos+n,cmp);
	ll ans=0;
	for (int i=1;i<n;++i){
	  int x=find(pos[i]),y=find(pos[i]-1);
	  ans+=(ll)siz[x]*siz[y]*height[pos[i]];
		fa[x]=y;
		siz[y]+=siz[x];
	}
	printf("%lld\n",(ll)n*(n+1)*(n-1)/2-ans-ans);
	return 0;
}
