#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int N=100005;
int n,m,fa[N],dep[N],pos[N],rmq[N*2][20],cnt,dfn,last[N],lg[N*2],size[N],root;
bool vis[N],clo[N];
struct edge{int to,next;}e[N*2];
struct Heap{
  priority_queue<int> a,b;
	void push(int x){a.push(x);}
	void erase(int x){b.push(x);}
	void pop(){
    while (b.size()&&a.top()==b.top()) a.pop(),b.pop();
    a.pop();
  }
  int top(){
    while (b.size()&&a.top()==b.top()) a.pop(),b.pop();
    if (!a.size()) return 0;
    else return a.top();
  }
  int size(){
    return a.size()-b.size();
  }
  int stop(){
    if (size()<2) return 0;
    int x=top();pop();
    int y=top();push(x);
    return y;
  }
}a,b[N],c[N];
//b:表示该节点的子树到达其父亲的路径
//c:表示该节点所有儿子的b的堆顶
//a:存储所有b的最大值+次大值
void addedge(int u,int v){
  e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
  e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;
}
void dfs(int x,int fa){
  dep[x]=dep[fa]+1;pos[x]=++dfn;rmq[dfn][0]=dep[x];
  for (int i=last[x];i;i=e[i].next){
    if (e[i].to==fa) continue;
    dfs(e[i].to,x);
    rmq[++dfn][0]=dep[x];
  }
}
int get_dis(int x,int y){
  int l=pos[x],r=pos[y];
  if (l>r) swap(l,r);
  int len=lg[r-l+1],mn=min(rmq[l][len],rmq[r-(1<<len)+1][len]);
  return dep[x]+dep[y]-2*mn;
}
void getsize(int u,int fa){
  size[u]=1;
  for (int i=last[u];i;i=e[i].next)
  if (e[i].to!=fa&&!vis[e[i].to]){
    getsize(e[i].to,u);
    size[u]+=size[e[i].to];
  }
}//预处理size
int getroot(int u,int fa,int ma){
  for (int i=last[u];i;i=e[i].next)
  if (e[i].to!=fa&&!vis[e[i].to]&&size[e[i].to]+size[e[i].to]>ma) return getroot(e[i].to,u,ma);
  return u;
}//找重心
void build(int x,int y){
  vis[x]=1;fa[x]=y;
  for (int i=last[x];i;i=e[i].next){
    if (vis[e[i].to]) continue;
		getsize(e[i].to,0);
    root=getroot(e[i].to,0,size[e[i].to]);
    build(root,x);
  }
}
void turn_off(int u,int v){
  if (u==v){
		c[u].push(0);
		if (c[u].size()==2) a.push(c[u].top());
	}
	if (!fa[u]) return;
	int f=fa[u],d=get_dis(v,f),tmp=b[u].top();
	b[u].push(d);
	if (d>tmp){
		int mx=c[f].top()+c[f].stop(),size=c[f].size();
		if (tmp) c[f].erase(tmp);
		c[f].push(d);
		int now=c[f].top()+c[f].stop();
		if (now>mx){
			if (size>=2) a.erase(mx);
			if (c[f].size()>=2) a.push(now);
		}
	}
	turn_off(f,v);
}
void turn_on(int u,int v){
  if (u==v){
    c[u].erase(0);
    if (c[u].size()==1) a.erase(c[u].top());
  }
  if (!fa[u]) return;
  int f=fa[u],d=get_dis(v,f),tmp=b[u].top();
  b[u].erase(d);
  if (d==tmp){
    int mx=c[f].top()+c[f].stop(),size=c[f].size();
    c[f].erase(d);
    if (b[u].size()) c[f].push(b[u].top());
    int now=c[f].top()+c[f].stop();
    if (now<mx){
      if (size>=2) a.erase(mx);
      if (c[f].size()>=2) a.push(now);
    }
  }
  turn_on(f,v);
}
int main(){
  scanf("%d",&n);
  for (int i=1;i<n;i++){
    int x,y;
    scanf("%d%d",&x,&y);
    addedge(x,y);
  }
  dfs(1,0);	
	for (int i=1;i<=dfn;i++) lg[i]=log(i)/log(2);
  for (int j=1;j<=lg[dfn];j++)
    for (int i=1;i<=dfn-(1<<j)+1;i++)
    rmq[i][j]=min(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
  //cout<<"YES"<<endl;	
	getsize(1,0);
  root=getroot(1,0,size[1]);
  build(root,0);
  for (int i=1;i<=n;i++) clo[i]=1,turn_off(i,i); 
	scanf("%d",&m);
  while (m--){
    char ch[2];
    scanf("%s",ch);
    if (ch[0]=='C'){
    	int x;
    	scanf("%d",&x);
      if (clo[x]) clo[x]=0,turn_on(x,x);
      else clo[x]=1,turn_off(x,x);
    }else printf("%d\n",a.top());
  }
  return 0;
}
