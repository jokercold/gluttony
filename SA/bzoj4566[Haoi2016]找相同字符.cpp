#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 200100
char s[N*2];
int n,cnta[N*2],cntb[N*2],sa[N*2],rank[N*4],a[N*2],b[N*2],tsa[N*2],height[N*2],g[N*2],f[N*2],A[N*2],B[N*2];
#define ll long long
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
  return (f[x]==x)?x:f[x]=find(f[x]);
}
#define N 200100
char ch1[N],ch2[N];
int main(){
	scanf("%s",ch1+1);
	scanf("%s",ch2+1);
	int len1=strlen(ch1+1);
	int len2=strlen(ch2+1);
	n=len1+len2+1;
	for (int i=1;i<=n;++i)
	if (i==len1+1) s[i]=27;
	else s[i]=(i<=len1)?ch1[i]-'a'+1:ch2[i-len1-1]-'a'+1;
  Get_SA();
	Get_Height();
  for (int i=1;i<=n;++i){
	  g[i]=i+1;
		f[i]=i;
		if (sa[i]<=len1) A[i]=1;
		if (sa[i]>len1+1) B[i]=1;
	}
	sort(g+1,g+n,cmp);
	ll ans=0;
	for (int i=1;i<=n-1;++i){
	  int x=find(g[i]),y=find(g[i]-1);
	  ans+=((ll)A[x]*B[y]+(ll)A[y]*B[x])*height[g[i]];
		A[y]+=A[x];B[y]+=B[x];
		f[x]=y;
	}
	printf("%lld\n",ans);
	return 0;
}
