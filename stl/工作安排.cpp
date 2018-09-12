#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
#define N 1000010
#define LL long long
#define rep(i,a,b) for (int i=a;i<=b;++i)
LL f[N],g[N];
LL a[N],q[N];
int main()
{
    LL n,k,C;
    scanf("%lld%lld%lld",&n,&k,&C);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    g[0]=a[1]*a[1];
    int head=1,tail=1;
    rep(i,1,n){
        if(i>=k+k){
            while(head<tail&&g[q[tail]]-g[i-k]>2*a[i]*(a[q[tail]+1]-a[i-k+1])) tail--;
            q[++tail]=i-k;
            while(head<tail&&g[q[head]]-g[q[head+1]]>2*a[i]*(a[q[head]+1]-a[q[head+1]+1])) head++;
        }
        int j=q[head];
        f[i]=g[j]+a[i]*a[i]-2*a[i]*a[j+1]+C;
        g[i]=f[i]+a[i+1]*a[i+1];
    }
    printf("%lld\n",f[n]);
    return 0;
}
