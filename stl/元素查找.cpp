#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<map>
using namespace std;
map<int,int>a;
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[x]++;
    }
    int m;
    scanf("%d",&m);
    for (int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        printf("%d\n",a[x]);
    }
    return 0;
}
