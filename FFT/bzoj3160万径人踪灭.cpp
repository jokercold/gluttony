#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define M 1000000007
#define ll long long
const double pi=acos(-1.0);
int n,L;
struct complex{
	double r,v;
	inline complex operator +(const complex &a){
		return (complex){r+a.r,v+a.v};
	}
	inline complex operator -(const complex &a){
		return (complex){r-a.r,v-a.v};
	}
	inline complex operator *(const complex &a){
		return (complex){r*a.r-v*a.v,r*a.v+v*a.r};
	}
}a[300100],b[300100],w[300100];
void FFT(complex *a,int f){
	for (int i=0,j=0;i<L;++i){
		if (i>j) swap(a[i],a[j]);
		for (int k=L>>1;(j^=k)<k;k>>=1);
	}
	for (int len=2;len<=L;len<<=1){
		int l=len>>1;
		complex W=(complex){cos(pi/l),f*sin(pi/l)};
		for (int i=1;i<l;++i) w[i]=w[i-1]*W;
		for (int i=0;i<L;i+=len){
			for (int j=0;j<l;++j){
				complex x=a[i+j],y=w[j]*a[i+j+l];
				a[i+j]=x+y;a[i+j+l]=x-y;
			}
		}
	}
	if (f==-1) for (int i=0;i<L;++i) a[i].r/=L;
}
char ch[100100],str[300100];
int ans[300100],ff[300100];
ll bin[300100];
ll SSS;
void manacher(){
	int N=n+n+1;
  for (int i=0;i<n;++i){
		str[i+i]='#';
		str[i+i+1]=ch[i];
	}
	str[n+n]='#';
	int mx=0,id=0;
	for (int i=0;i<N;++i){
		if (mx>i) ff[i]=min(ff[id+id-i],mx-i);else ff[i]=1;
		while (i-ff[i]>=0&&i+ff[i]<N&&str[i-ff[i]]==str[i+ff[i]]) ff[i]++;
		if (ff[i]+i>mx) mx=ff[i]+i,id=i;
		SSS-=(ff[i]/2);
		if (SSS<0) SSS+=M;
	}
}

int main(){
  scanf("%s",ch);
	n=strlen(ch);
	L=1;
	while (L<n+n) L<<=1;
	w[0]=(complex){1.0,0.0};

  for (int i=0;i<n;++i)
  if (ch[i]=='a') a[i]=(complex){1.0,0.0};
	else a[i]=(complex){0.0,0.0};
	FFT(a,1);
	for (int i=0;i<L;++i) a[i]=a[i]*a[i];
	FFT(a,-1);
	for (int i=0;i<n+n-1;++i) ans[i]=(int)(a[i].r+0.5);

  for (int i=0;i<n+n-1;++i) a[i].r=a[i].v=0.0;
	for (int i=0;i<n;++i)
	if (ch[i]=='b') a[i]=(complex){1.0,0.0};
	else a[i]=(complex){0.0,0.0};
	FFT(a,1);
	for (int i=0;i<L;++i) a[i]=a[i]*a[i];
	FFT(a,-1);
	for (int i=0;i<n+n-1;++i) ans[i]+=(int)(a[i].r+0.5);
  
	bin[0]=1;
	for (int i=1;i<=n;++i) bin[i]=bin[i-1]*2%M;
	SSS=0;
	for (int i=0;i<n+n-1;i++){
		//cout<<i<<" "<<ans[i]<<endl;
		SSS=SSS+bin[(ans[i]+1)/2]-1;
		if (SSS>=M) SSS-=M;
	}
	//cout<<SSS<<endl;
	manacher();
	printf("%lld\n",SSS);
	return 0;
}

