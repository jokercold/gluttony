#include<iostream>
#include<cstdio>
#include<set>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
multiset <int> q1,q2;
multiset <int> ::iterator it,it2;
int main(){
    int T;
    scanf("%d",&T);
    int ans=0;
    while(T--){
          int kk,x;
          scanf("%d%d",&kk,&x);
          if (!kk){
             if(q2.size()==0)q1.insert(x);
             else{
                  it=q2.lower_bound(x);
                  if (it==q2.begin()){
                     ans+=abs(*it-x)%1000000;
                     ans%=1000000;
                     q2.erase(it);
                  }else{
                        it2=it;
                        --it2;
                        if (it==q2.end()){
                           ans+=abs(*it2-x)%1000000;
                           ans%=1000000;
                           q2.erase(it2);
                        }else{
                              if (abs(*it2-x)<=abs(*it-x)){
                                  ans+=abs(*it2-x)%1000000;
                                  ans%=1000000;
                                  q2.erase(it2);
                              }else{
                                    ans+=abs(*it-x)%1000000;
                                    ans%=1000000;
                                    q2.erase(it);
                              }
                        }
                  }
             }
          }else{
             if(q1.size()==0)q2.insert(x);
             else{
                  it=q1.lower_bound(x);
                  if (it==q1.begin()){
                     ans+=abs(*it-x);
                     ans%=1000000;
                     q1.erase(it);
                  }else{
                        it2=it;
                        --it2;
                        if (it==q1.end()){
                           ans+=abs(*it2-x);
                           ans%=1000000;
                           q1.erase(it2);
                        }else{
                              if (abs(*it2-x)>abs(*it-x)){
                                  ans+=abs(*it-x)%1000000;
                                  ans%=1000000;
                                  q1.erase(it);
                              }else{
                                    ans+=abs(*it2-x)%1000000;
                                    ans%=1000000;
                                    q1.erase(it2);
                              }
                        }
                  }
             }
          }
    }
    printf("%d\n",ans%1000000);
    //while (1);
    return 0;
}
