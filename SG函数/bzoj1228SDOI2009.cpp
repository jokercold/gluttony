#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
inline int in(int x=0,char ch=getchar(),int v=1){
  while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-') v=-1,ch=getchar();
  while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*v;
}
inline int GetSG(int n,int m){
  if((n&1)&&(m&1)) return 0;
  if(!(n&1)&&!(m&1)) return GetSG(n/2,m/2)+1;
  return (n&1)?GetSG((n+1)/2,m/2)+1:GetSG(n/2,(m+1)/2)+1;
}
int main(){
	int t,n,a,b,ans=0;
	t=in();
	while(t--){
		n=in();n/=2;ans=0;
		for(int i=1;i<=n;i++) a=in(),b=in(),ans^=GetSG(a,b);
		if(ans) puts("YES");else puts("NO");
	}
	return 0;
}
