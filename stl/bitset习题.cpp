#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<bitset>
using namespace std;
#define per(i,a,b) for (int i=a;i>=b;--i)
bitset <3000000> f;
int main()
{
    int n;
    scanf("%d",&n);
    f[0]=1;
    for (int i=1;i<=n;++i)
    {
        int a;
        scanf("%d",&a);
        f=f^(f<<a);
    }
    int ans=0;
    per(i,2000000,1)
    if (f[i])
       ans^=i;
    printf("%d\n",ans);
    return 0;
}
