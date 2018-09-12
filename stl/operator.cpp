#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
//#define ll long long
#define rep(i,a,b) for (int i=a;i<=b;++i)
#define per(i,a,b) for (int i=a;i>=b;--i)
pair<int,int>a[1000];
ll mo(ll a,ll pp)
{
   if (a>0&&a<pp)return a;
   a%=pp;
   if (a<0)a+=pp;
   return a;
}
struct node
{
    int x,y;
};
bool operator <(node a,node b){
     return ((a.x<b.x)||(a.x==b.x)&&(a.y<b.y));
}
bool operator >(node a,node b){
     return ((a.x>b.x)||(a.x==b.x)&&(a.y>b.y));
}
priority_queue <node> Q;
priority_queue <node,vector<node>,greater<node> >Q1;
int main()
{
    int n;
    scanf("%d",&n);
    rep(i,1,n)     
    {
       int a;
       Q.push((node){scanf("%d",&a),i});
    }
}
