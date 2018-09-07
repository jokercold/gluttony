#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 200500
char ss[N];
int n;
int cnta[N],cntb[N],sa[N],a[N],b[N],rank[N*2],tsa[N];
void Get_SA(){
  for (int i=0;i<=256;++i) cnta[i]=0;
	for (int i=1;i<=n;++i) cnta[(int)ss[i]]++;
	for (int i=1;i<=256;++i) cnta[i]+=cnta[i-1];
	for (int i=n;i>=1;--i) sa[cnta[(int)ss[i]]--]=i;
	rank[sa[1]]=1;
	for (int i=2;i<=n;++i) rank[sa[i]]=rank[sa[i-1]]+(ss[sa[i]]!=ss[sa[i-1]]);
  /*for (int i=1;i<=n;++i)
		cout<<i<<" "<<rank[i]<<endl;*/
	for (int i=1;rank[sa[n]]!=n;i<<=1){
	  for (int j=1;j<=n;++j) a[j]=rank[j],b[j]=rank[j+i];
		for (int j=0;j<=n;++j) cnta[j]=0,cntb[j]=0;
		for (int j=1;j<=n;++j) cnta[a[j]]++,cntb[b[j]]++;
    for (int j=1;j<=n;++j) cnta[j]+=cnta[j-1],cntb[j]+=cntb[j-1];
		for (int j=n;j>=1;--j) tsa[cntb[b[j]]--]=j;
		for (int j=n;j>=1;--j) sa[cnta[a[tsa[j]]]--]=tsa[j];
		rank[sa[1]]=1;
		for (int j=2;j<=n;++j)
			rank[sa[j]]=rank[sa[j-1]]+(a[sa[j]]!=a[sa[j-1]]||b[sa[j]]!=b[sa[j-1]]);
	}
	//cout<<"YES"<<endl;
}
int main(){
  scanf("%s",ss+1);
  //cout<<(ss+1)<<endl;
	int nn=strlen(ss+1);
	for (int i=1;i<=nn;++i)
		ss[i+nn]=ss[i];
	n=nn+nn;
	//cout<<(ss+1)<<endl;
	//cout<<n<<endl;
	Get_SA();
	//cout<<"ha"<<endl;
	for (int i=1;i<=n;++i)
	if (sa[i]<=nn)
	  printf("%c",ss[sa[i]+nn-1]);
	printf("\n");
	return 0;
}
