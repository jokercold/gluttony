#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<queue>
using namespace std;
priority_queue <int>q;
priority_queue <int,vector<int>,greater<int> >q1;
int a[2000000];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        int m;
        scanf("%d",&m);
        for (int i=1;i<=m;++i)
        {
            int x;
            scanf("%d",&x);
            q.push(x);
            q1.push(x);
        }
        int x=q.top();
        q.pop();
        int y=q1.top();
        q1.pop();
        printf("%d %d\n",x,y);
    }
    return 0;
}
