#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[2000000];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for (int i=1;i<=n-1;++i)
        printf("%d ",a[i]);
    printf("%d\n",a[n]);
    //while (1);
    return 0;
}
