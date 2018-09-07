#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char ch[200000];
int main(){
	scanf("%s",ch);
	int n=strlen(ch);
	int num=0;
	int ans=0;
	for (int i=0;i<n;++i)
	if (ch[i]=='(') ++num;
	else{
		if (num==0) num++,ans++;
		else --num;
	}
	ans+=num/2;
	printf("%d\n",ans);
	return 0;
}
