#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char ch[20];
int st[200];
int ff[200];
bool flag[50];
int main(){
	int cas;
	scanf("%d",&cas);
	while (cas--){
		int n;
		scanf("%d",&n);
		scanf("%s",ch);
		for (int i=0;i<=30;++i) flag[i]=false;
		int num=0;
		if (ch[2]=='1') num=0;
		else{
			for (int i=4;i<strlen(ch);++i)
			if (ch[i]==')') break;
			else	num=num*10+(ch[i]-'0');
		}
		int ans=0;
		int top=0;
		int now=0;
		bool FF=true;
		while (n--){
			scanf("%s",ch);
			if (ch[0]=='F'){
				scanf("%s",ch); 
				if (flag[ch[0]-'a']==true) ans=-1;
				flag[ch[0]-'a']=true;
				++top;
				ff[top]=ch[0]-'a';
				scanf("%s",ch);
				int aa=0;
		   	if (ch[0]=='n') aa=101;
				else{ 
					for (int i=0;i<strlen(ch);++i)
						aa=aa*10+(ch[i]-'0');
				}
				scanf("%s",ch);
				int bb=0;
			  if (ch[0]=='n') bb=101;
				else{
					for (int i=0;i<strlen(ch);++i)
						bb=bb*10+(ch[i]-'0');
				}
				if (ans==-1) continue;
			  if (aa>bb) FF=false;
				if (aa<101&&bb==101&&FF==true) st[top]=1;
				else st[top]=0;
				if (FF==false) st[top]=-1;
			  if (st[top]!=-1) now+=st[top];
			}else{
				if (ans==-1) continue;
				if (top<=0){
					ans=-1;
					continue;
				}
				ans=max(ans,now);
				if (st[top]!=-1)	now-=st[top];
				else FF=true;
				flag[ff[top]]=false;
				--top;
			}
	  }
		if (top>0) ans=-1;
		//cout<<ans<<" "<<num<<endl;
		if (ans==-1) printf("ERR\n");
		else if (ans==num) printf("Yes\n");
		else printf("No\n");
  }
	return 0;
}
