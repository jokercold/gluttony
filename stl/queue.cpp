#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<queue>
using namespace std;
priority_queue<int>Q;
int a[2000000];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        Q.push(x);
    }
    for (int i=n;i>=1;--i)
    {
        int x=Q.top();
        Q.pop();
        a[i]=x;
    }
    for (int i=1;i<=n-1;++i)
        printf("%d ",a[i]);
    printf("%d\n",a[n]);
    return 0;
}
