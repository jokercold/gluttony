#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){
  int f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	return f*tmp;
}
#define ll long long
#define N 1001000
int q[N];
ll sump[N],extra[N],dp[N],C[N],X[N];
ll cal(int j,int i){
  return dp[j]-X[i]*sump[j]+extra[j];
}
bool check(int j,int k,int i){
  return (dp[k]+extra[k]-dp[j]-extra[j])*(sump[i]-sump[k])>(dp[i]+extra[i]-dp[k]-extra[k])*(sump[k]-sump[j]);
}
int main(){
  int n;n=read();
	for (int i=1;i<=n;++i){
		int p;
	  X[i]=read();p=read();C[i]=read();		
		sump[i]=sump[i-1]+p;
		extra[i]=extra[i-1]+X[i]*p;
	}
	dp[0]=0;
	int hed=0,tail=0;
	for (int i=1;i<=n;++i){
		while (hed<tail&&cal(q[hed],i)>cal(q[hed+1],i)) ++hed;
		int hh=q[hed];
    dp[i]=dp[hh]+C[i]+X[i]*(sump[i]-sump[hh])-extra[i]+extra[hh];
    //cout<<sump[i]-sump[hh]<<endl;
		//cout<<hh<<" "<<i<<" "<<dp[i]<<endl;
		while (hed<tail&&check(q[tail-1],q[tail],i)) tail--;
		++tail;
		q[tail]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
