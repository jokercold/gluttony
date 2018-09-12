#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<map>
#include<queue>
using namespace std;
typedef long long ll;
map<int,bool>a;
priority_queue<ll,vector<ll>,greater<ll> >Q;
void add(ll x){
     if (a[x]) return;
     a[x]=1;
     Q.push(x);
}
int main()
{
    int n;
    scanf("%d",&n);
    Q.push(1);
    while (n--)
    {
        ll t=Q.top();Q.pop();
        if (!n) cout<<t<<endl;
        add(t*2),add(t*3);add(t*5);
    }
    return 0;
}
