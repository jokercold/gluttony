#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
#define ll long long
#define N 10000000
#define M 1000000007
map<ll,ll>mp;
bool vis[N+100];
int phi[N+100],prime[N+100],sum[N+100];
ll X;
ll TJJ=N;
void pre(){
  vis[1]=phi[1]=1;
	sum[1]=1;
	int num=0;
	for (int i=2;i<=TJJ;++i){
	  if (!vis[i]){prime[++num]=i;phi[i]=i-1;}
		for (int j=1;j<=num;++j){
		  if ((ll)i*prime[j]>TJJ) break;
			vis[i*prime[j]]=true;
			if (i%prime[j]) phi[i*prime[j]]=phi[i]*phi[prime[j]];
			else{
				phi[i*prime[j]]=phi[i]*prime[j];
			  break;
			}	
		}
		sum[i]=(sum[i-1]+(ll)i*phi[i]%M)%M;
	}
}
ll solve(ll n){
	//cout<<n<<endl;
  if (n<=N) return sum[n];
	if (mp[n]) return mp[n];
	ll ans=(ll)n*(n+1)%M*(n+n+1)%M*X%M;
	int last=0;
	for (int i=2;i<=n;i=last+1){
		last=n/(n/i);
		ans=(ans-((ll)last+i)*(last-i+1)/2%M*solve(n/i)%M+M)%M;
	}
	mp[n]=ans;
	return ans;
}
ll mi(ll x,ll y){
  ll t=1;
	while (y){
		if (y&1) t=t*x%M;
		x=x*x%M;
		y>>=1;
	}
	return t;
}
int main(){
  ll n;
	scanf("%lld",&n);
	TJJ=min(TJJ,n);
	pre();
	X=mi(6,M-2);
 	printf("1\n%lld\n",solve(n));
	return 0;
}
