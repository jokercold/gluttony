#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
#define M 998244353
#define G 3
#define N 200100
int n,k,L;
ll inv[N],F[N],Finv[N],Q[N],INV,a[N*4],b[N*4],w[N*4];
ll mi(ll x,int y){
	ll ans=1;
	while (y){
		if (y&1) ans=ans*x%M;
		x=x*x%M;
		y>>=1;
	}
	return ans;
}
void NTT(ll *a,int f){
	for (int i=0,j=0;i<L;++i){
		if (i>j) swap(a[i],a[j]);
		for (int k=L>>1;(j^=k)<k;k>>=1);
	}
	for (int len=2;len<=L;len<<=1){
		int l=len>>1;
		ll W=mi(G,(M-1)/len);
		for (int i=1;i<l;++i) w[i]=w[i-1]*W%M;
		for (int i=0;i<L;i+=len)
			for (int j=0;j<l;++j){
				ll x=a[i+j],y=w[j]*a[i+j+l]%M;
				a[i+j]=(x+y>=M)?x+y-M:x+y;
				a[i+j+l]=(x-y<0)?x-y+M:x-y;
			}
	}
	if (f==-1){
		for (int i=1;i<L/2;++i) swap(a[i],a[L-i]);
		for (int i=0;i<L;++i) a[i]=a[i]*INV%M;
	}
}	
int main(){
	scanf("%d%d",&n,&k);
	inv[1]=1;
	for (int i=2;i<=k;++i) inv[i]=(ll)(M-M/i)*inv[M%i]%M;
	F[0]=Finv[0]=Q[0]=w[0]=1;
	for (int i=1;i<=k;++i) F[i]=F[i-1]*i%M,Finv[i]=Finv[i-1]*inv[i]%M;
	for (int i=1;i<=k;++i) Q[i]=Q[i-1]*(n-i)%M;
	a[0]=1;b[0]=0;
	for (int i=1;i<=k;++i) a[i]=a[i-1]*(-1)*inv[i]%M;
	for (int i=1;i<=k;++i) b[i]=Finv[i]*mi(i,k)%M;
	L=1;
	while (L<k+k) L<<=1;
	INV=mi(L,M-2);
	NTT(a,1);NTT(b,1);
	for (int i=0;i<L;++i) a[i]=a[i]*b[i]%M;
	NTT(a,-1);
	ll ans=0;
	int Min=min(k,n-1);
	for (int i=0;i<=Min;++i)(ans+=F[i]*mi(2,n-i-1)%M*a[i]%M*Q[i]%M*Finv[i]%M)%=M;
	if (ans<0) ans+=M;
  ans=ans*n%M*mi(2,(ll)(n-1)*(n-2)/2%(M-1))%M;
	printf("%lld\n",ans);
	return 0;
}
