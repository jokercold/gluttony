#include<iostream>
#include<cstdio>
#include<set>
#pragma G++ optimize (2)
using namespace std;
char ch[50];
struct node{
  int l,r;
};
struct cmp{
  bool operator()(node a,node b){
	  return a.l==b.l?a.r<b.r:a.l<b.l;
	}
};
multiset<node,cmp> st;
int main(){
  int T;
	scanf("%d",&T);
	while (T--){
	  scanf("%s",ch);
		if (ch[0]=='A'){
		  int Start,End;
			scanf("%d%d",&Start,&End);
			node x=(node){Start,End};
			int ans=0;
			while (!st.empty()){
        multiset<node,cmp>::iterator it=st.lower_bound(x);
        if ((*it).l<=x.r&&x.l<=(*it).r){
				  ans++;
					st.erase(it);
				}else break;
			}
			while (!st.empty()){
			  multiset<node,cmp>::iterator it=st.lower_bound(x);
				if (it!=st.begin()){
				  it--;
					if ((*it).l<=x.r&&x.l<=(*it).r){
					  ans++;
						st.erase(it);
					}else break;
				}else break;
			}
			st.insert(x);
		  printf("%d\n",ans);
		}else printf("%d\n",st.size());
	}
	return 0;
}
