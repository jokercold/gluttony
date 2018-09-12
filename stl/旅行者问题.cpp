#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
long long a[200000];
int main(){
    int n;
    scanf("%d",&n);
    rep(i,1,n)scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    long long t=1;
    long long ans=0;
    rep(i,1,n)
        ans+=t*(a[i]-a[i-1])*(n-i+1),t+=2;
    long long ans1=n;
    t=__gcd(ans,ans1);
    printf("%lld %lld\n",ans/t,ans1/t);
    //while (1);
    return 0;
}
