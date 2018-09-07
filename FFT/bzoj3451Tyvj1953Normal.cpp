#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
using namespace std;
const double pi=acos(-1.0);
const int N=90010;
int n,tot,Next[N<<1],head[N],tree[N<<1],L,H,size[N],Maxdep,Max;
ll Ans[N<<1],f[N<<1],g[N<<1],sum[N<<1];
bool vis[N];
struct complex{
	double r,v;
	inline complex operator + (const complex &a) { return (complex){r+a.r,v+a.v};}
	inline complex operator - (const complex &a) { return (complex){r-a.r,v-a.v};}
	inline complex operator * (const complex &a) { return (complex){r*a.r-v*a.v,r*a.v+v*a.r};}
}a[N<<2],b[N<<2],w[N<<2];
void FFT(complex *a,int f){
	for (int i=0,j=0;i<L;i++){
		if (i>j) swap(a[i],a[j]);
		for (int k=L>>1;(j^=k)<k;k>>=1);
	}
	for (int len=2;len<=L;len<<=1){
		int l=len>>1;
		complex W=(complex){cos(pi/l),f*sin(pi/l)};
		for(int i=1;i<l;i++) w[i]=w[i-1]*W;
		for (int i=0;i<L;i+=len)
			for (int j=0;j<l;j++){
				complex x=a[i+j],y=w[j]*a[i+j+l];
				a[i+j]=x+y;a[i+j+l]=x-y;
			}
	}
	if (f==-1){
		for (int i=0;i<L;i++) a[i].r/=L;
	}
}
void mul(ll *A,ll *B,int n,int m){
	n++;m++;
	w[0]=(complex){1.0,0.0};
	L=1;H=0;
	while (L<n+m) L<<=1,H++;
	for (int i=0;i<=L;i++) a[i]=b[i]=(complex){0.0,0.0};
	for (int i=0;i<n;i++) a[i].r=A[i];
	for (int i=0;i<m;i++) b[i].r=B[i];
	FFT(a,1);FFT(b,1);
	for (int i=0;i<L;i++) a[i]=a[i]*b[i];
	FFT(a,-1);
	for (int i=0;i<n+m-1;i++) A[i]=(ll)(a[i].r+0.5);
}
void add(int x,int y){
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
ll mi(ll x,int y){
	ll ans=1;
	while (y){
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
void Get_Size(int u,int fa){
	size[u]=1;
	for (int i=head[u];i;i=Next[i]){
		int v=tree[i];
		if (v==fa||vis[v]) continue;
		Get_Size(v,u);
		size[u]+=size[v];
	}
}
int Get_root(int u,int fa,int S){
	for (int i=head[u];i;i=Next[i]){
		int v=tree[i];
		if (v==fa||vis[v]) continue;
		if (size[v]+size[v]>S) return Get_root(v,u,S);
	}
	return u;
}
void dfs(int u,int fa,int dep){
	f[dep]++;Ans[dep+1]+=2;
	Maxdep=max(Maxdep,dep);
	for (int i=head[u];i;i=Next[i]){
		int v=tree[i];
		if (v==fa||vis[v]) continue;
		dfs(v,u,dep+1);
	}
}
void TDC(int u){
	Get_Size(u,0);
	int t=Get_root(u,0,size[u]);
	vis[t]=1;
	int Max=0;
	for (int i=head[t];i;i=Next[i]){
		int v=tree[i];
		if (vis[v]) continue;
		Maxdep=0;
		dfs(v,t,1);
		Max=max(Max,Maxdep);
		for (int j=1;j<=Maxdep;j++) g[j]=f[j];
		for (int j=1;j<=Maxdep;j++) sum[j]+=f[j];
		mul(f,g,Maxdep,Maxdep);
		for (int j=2;j<=Maxdep+Maxdep;j++) Ans[j+1]-=f[j],f[j]=g[j]=0;
	}
	for (int j=1;j<=Max;j++) g[j]=sum[j];
	mul(sum,g,Max,Max);
	for (int j=2;j<=Max+Max;j++) Ans[j+1]+=sum[j];
	for (int j=1;j<=Max+Max;j++) sum[j]=g[j]=0;
	for (int i=head[t];i;i=Next[i]){
		int v=tree[i];
		if (!vis[v]) TDC(v);
	}
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		x++;y++;
		add(x,y);add(y,x);
	}
	TDC(1);
	long double ans=0;
	Ans[1]=n;
	for (int i=1;i<=n;i++) ans=ans+(long double)Ans[i]/i;
	printf("%.4Lf\n",ans);
	return 0;
}
