#include<iostream>
#include<cstdio>
#include<set>
#define rep(i,a,b) for (int i=a;i<=b;++i)
using namespace std;
set<int>q;
set<int>::iterator it;
int main(){
    int n,m;
    rep(i,1,n){
       int x;
       scanf("%d",&x);
       q.insert(x);
    } 
    rep(i,1,m){
       int x;
       scanf("%d",&x);
       it=q.find(x);
       if (it==q.end())printf("no");
       else printf("yes");
    }
    rep(i,1,m){
       int x;
       scanf("%d",&x);
       it=q.lower_bound(x);
       //upper_bound(x);
       if (it==q.end())printf("no");
       else printf("%d\n",*it);
    }
    for (it=q.begin();it!=q.end();++it)printf("%d\n",*it);
}
