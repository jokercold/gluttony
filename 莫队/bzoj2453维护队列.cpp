#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=1e4+5, M=1e6+5;
inline int read(){
	char c=getchar();int x=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
} 
int n,Q,a[N],pos[N],m,block,t[N],x,y;
char op[3];
struct meow{
	int l,r,tim,id;
	bool operator <(const meow &a) const{
		return pos[l]==pos[a.l] ? ( pos[r]==pos[a.r] ? tim<a.tim : pos[r]<pos[a.r]) : pos[l]<pos[a.l];
	}
}q[N];
struct cmeow{int p,v,last;}cq[N];
int p,tim, ans[N];
int c[M], now;
int l=1,r=0,cur=0;
inline void add(int x) {now+= (++c[x])==1;}
inline void del(int x) {now-= (--c[x])==0;}
inline void cha(int p,int v){
	if(l<=p && p<=r) add(v), del(a[p]);
	a[p]=v;
}
void modui(){
	for(int i=1;i<=p;i++){
		while(cur<q[i].tim) cur++, cha(cq[cur].p, cq[cur].v);
		while(cur>q[i].tim) cha(cq[cur].p, cq[cur].last), cur--;
		while(r<q[i].r) r++, add(a[r]);
		while(r>q[i].r) del(a[r]), r--;
		while(l<q[i].l) del(a[l]), l++;
		while(l>q[i].l) l--, add(a[l]);
		ans[ q[i].id ]=now;
	}
}
int main(){
	//freopen("in","r",stdin);
	n=read(); Q=read();
	block=sqrt(n); m=(n-1)/block+1;
	for(int i=1;i<=n;i++) a[i]=t[i]=read(), pos[i]=(i-1)/block+1;
	for(int i=1;i<=Q;i++){
		scanf("%s",op); x=read(); y=read();
		if(op[0]=='Q') q[++p]=(meow){x, y, tim, p};
		else cq[++tim]=(cmeow){x, y, t[x]}, t[x]=y;
	}
	sort(q+1, q+1+p);
	modui();
	for(int i=1;i<=p;i++) printf("%d\n",ans[i]);
}
