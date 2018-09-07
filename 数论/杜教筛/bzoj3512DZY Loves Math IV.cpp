#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
#define N 2000000
#define M 1000000007
#define ll long long
map<ll,int>mp,one;
int phi[N+10],sum[N+10],rest[N+10],prime[N];
bool visit[N+10];
void pre(){
  rest[1]=phi[1]=visit[1]=1;
	int num=0;
	for (int i=2;i<=N;++i){
	  if (!visit[i]) prime[++num]=i,phi[i]=i-1,rest[i]=i;
		for (int j=1;j<=num;++j){
		  if ((ll)i*prime[j]>N) break;
		  visit[i*prime[j]]=true;
			if (i%prime[j]){
			  phi[i*prime[j]]=phi[i]*phi[prime[j]];
				rest[i*prime[j]]=rest[i]*prime[j];
			}else{
				phi[i*prime[j]]=phi[i]*prime[j];
				rest[i*prime[j]]=rest[i];
				break;
			}
		}
	}
	for (int i=1;i<=N;++i) sum[i]=(sum[i-1]+phi[i])%M;
}
int S(int n,int m){
  if (m<=1) return phi[n*m];
	if (n==1){
	  if (m<N) return sum[m];
		if (one[m]) return one[m];
		ll ans=(ll)m*(m+1)/2%M;
		int j=0;
		for (int i=2;i<=m;i=j+1){
		  j=m/(m/i);
			ans=(ans-(ll)(j-i+1)*S(1,m/i)%M+M)%M;
		}
		one[m]=ans;
		return ans;
	}else{
	  if (mp[(ll)n*M+m]) return mp[(ll)n*M+m];
		ll ans=0;
		for (int i=1;i*i<=n;i++)
		if (n%i==0){
		  ans=(ans+(ll)phi[n/i]*S(i,m/i)%M)%M;
			if (i*i!=n) ans=(ans+(ll)phi[i]*S(n/i,m/(n/i))%M)%M;
		}
		mp[(ll)n*M+m]=ans;
		return ans;
	}
}
int main(){
  int n,m;
	scanf("%d%d",&n,&m);
  if (n>m) swap(n,m);
	pre();
	ll ans=0;
	for (int i=1;i<=n;++i){
		ans=(ans+(ll)i/rest[i]*S(rest[i],m)%M)%M;
	}
	printf("%lld\n",ans);
	return 0;
}
