#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define M 101000
struct node{
	int vet,val,Next;
}edge[M][3];
#define ll long long
#define pr pair<ll,int>
#define mp make_pair
#define se second
priority_queue<pr,vector<pr> ,greater<pr> >Q;
int num;
int hed[20000][3];
void add(int u,int v,int w,int type){
  edge[num][type].vet=v;
	edge[num][type].val=w;
	edge[num][type].Next=hed[u][type];
	hed[u][type]=num;
}
ll dis[20000];
bool flag[20000];
int n;
void Dijkstra(int type,int S){
  for (int i=1;i<=n;++i) dis[i]=1ll<<60,flag[i]=false;
	dis[S]=0;
	Q.push(mp(dis[S],S));
	while (!Q.empty()){
    int u=Q.top().se;Q.pop();
		//cout<<u<<" "<<Q.top().first<<endl;
		if (flag[u]) continue;
    flag[u]=true;
		for (int i=hed[u][type];i!=-1;i=edge[i][type].Next){
		  int v=edge[i][type].vet;
			if (dis[v]>dis[u]+edge[i][type].val){
				dis[v]=dis[u]+edge[i][type].val;
				Q.push(mp(dis[v],v));
			}
		}
	}
}
int main(){
  int m;
	scanf("%d%d",&n,&m);
  num=0;
	for (int i=1;i<=n;++i)
		for (int j=0;j<=2;++j) hed[i][j]=-1;
	for (int i=1;i<=m;++i){
	  int u,v,P,Q;
		scanf("%d%d%d%d",&u,&v,&P,&Q);
		++num;
		add(v,u,P,0);
		add(v,u,Q,1);
		add(u,v,2,2);
	}
	Dijkstra(0,n);
	//cout<<"YES"<<endl;
	for (int i=1;i<=n;++i)
		for (int j=hed[i][0];j!=-1;j=edge[j][0].Next) 
		if (dis[edge[j][0].vet]==dis[i]+edge[j][0].val){
			edge[j][2].val--;
		  //cout<<i<<" "<<edge[j][0].vet<<endl;
		}
	//cout<<endl;
	Dijkstra(1,n);
	//cout<<"YES"<<endl;
	for (int i=1;i<=n;++i)
		for (int j=hed[i][1];j!=-1;j=edge[j][1].Next) 
		if (dis[edge[j][1].vet]==dis[i]+edge[j][1].val){
			edge[j][2].val--;
		  //cout<<i<<" "<<edge[j][2].vet<<" "<<edge[j][2].val<<endl;
			//cout<<i<<" "<<edge[j][0].vet<<endl;
		}
	/*for (int i=1;i<=n;++i)
		for (int j=hed[i][2];j!=-1;j=edge[j][2].Next) 
	    cout<<i<<" "<<edge[j][2].vet<<" "<<edge[j][2].val<<endl;*/
	Dijkstra(2,1);
	/*cout<<dis[1]<<" "<<dis[2]<<" "<<dis[4]<<" "<<dis[5]<<endl;*/
	printf("%lld\n",dis[n]);
  return 0;
}
