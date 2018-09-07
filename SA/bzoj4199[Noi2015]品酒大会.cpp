#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 400000
#define ll long long
int cnta[N],cntb[N],sa[N],tsa[N],rank[N<<1],height[N],a[N],b[N];
int TJJ[N];
int n;
char s[N<<1];
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
    //cout<<i<<endl;
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
ll ans[N],ret[N],cnt[N],mx[N],mi[N];
int siz[N],fa[N],pos[N];
int find(int x){
  return (fa[x]==x)?x:fa[x]=find(fa[x]);
}
void uni(int x,int y){
  fa[x]=y;
	siz[y]+=siz[x];
	ans[y]=max(max(ans[y],ans[x]),max(mx[x]*mx[y],mi[x]*mi[y]));
	ans[y]=max(ans[y],max(mx[x]*mi[y],mi[x]*mx[y]));
	mx[y]=max(mx[x],mx[y]);mi[y]=min(mi[x],mi[y]);
}
bool cmp(int x,int y){
  return height[x]>height[y];
}
int main(){
  scanf("%d",&n);
	scanf("%s",s+1);
	for (int i=1;i<=n;++i) scanf("%d",&TJJ[i]);
  Get_SA();
	Get_Height();
	for (int i=1;i<=n;++i){
		siz[i]=1;
		ans[i]=ret[i]=-1ll<<60;
		mx[i]=mi[i]=TJJ[sa[i]];
		fa[i]=i;
		pos[i]=i+1;
	}
	ret[0]=-1ll<<60;
	//for (int i=1;i<=n;++i) cout<<rank[i]<<" ";
	//cout<<endl;
	sort(pos+1,pos+n,cmp);
	for (int i=1;i<n;++i){
	  int x=find(pos[i]),y=find(pos[i]-1);
		//cout<<mx[x]<<" "<<mx[y]<<" "<<height[pos[i]]<<endl;
    cnt[height[pos[i]]]+=1ll*siz[x]*siz[y]; 
		uni(x,y);
    ret[height[pos[i]]]=max(ret[height[pos[i]]],ans[y]);
	}
	for (int i=n-2;i>=0;--i){
		cnt[i]+=cnt[i+1];
		ret[i]=max(ret[i],ret[i+1]);
	}
	for (int i=0;i<n;++i)
		printf("%lld %lld\n",cnt[i],(cnt[i])?ret[i]:0ll);
	return 0;
}
