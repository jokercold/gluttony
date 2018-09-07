#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#pragma G++ optimize (2)
using namespace std;
#define N 500500
#define ll long long
inline ll read(){
  char last='+',ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') last='-';ch=getchar();}
	ll tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	if (last=='-') tmp=-tmp;
	return tmp;
}
struct planet{
  ll k,b;
	int id;
}Pl[N];
bool cmp(planet x,planet y){
  return x.k>y.k;
}
struct Query{
  int s,id;
	ll x;
}Q[N];
bool cmp3(Query x,Query y){
  return x.x<y.x;
}
struct Line{
  ll k,b;
};
int hed[N],vet[N],Next[N];
int num,n,m;
int in[N],out[N];
bool cmp2(int x,int y){
  return in[x]<in[y];
}
vector<int>appear[N];
void add(int u,int v){
  ++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
bool cannot(Line a,Line b,Line c){
  if (b.k==c.k) return b.b>=c.b;
	return (b.b-a.b)*(a.k-c.k)>(c.b-a.b)*(a.k-b.k);
}
ll ans[N];
struct yanhan{
  vector<Line> vec;
  int now;
	yanhan():now(0){};
	void insert(ll k,ll b){
	  if (vec.size()<=1) vec.push_back((Line){k,b});
		else{
		  Line tmp=(Line){k,b};
			while (vec.size()>1&&cannot(vec[vec.size()-2],vec[vec.size()-1],tmp)) vec.pop_back();
			vec.push_back(tmp);
		}
	}
	ll calc(int x,int k){
	  return vec[k].k*x+vec[k].b;
	}
  ll query(int x){
	  if (vec.size()==0) return 1ll<<60;
		while((now<(vec.size())-1)&&(calc(x,now)>calc(x,now+1))) ++now;
		return calc(x,now);
	}
}T[N*4];
int cnt;
void dfs(int x){
  in[x]=++cnt;
	for (int i=hed[x];i!=-1;i=Next[i]) dfs(vet[i]);
	out[x]=cnt;
}
void insert(int p,int l,int r,int x,int y,int z){
	//cout<<l<<" "<<r<<" "<<x<<" "<<y<<endl;
  if (l>y||r<x) return;
	if(x<=l&&r<=y){
		//printf("Tree %d l=%d r=%d inserted %d %d\n", p, l, r, Pl[z].k, Pl[z].b);
	  T[p].insert(Pl[z].k,Pl[z].b);
		return;
	}
	int mid=(l+r)>>1;
	insert(p<<1,l,mid,x,y,z);
	insert(p<<1|1,mid+1,r,x,y,z);
}
ll query(int p,int l,int r,int pos,int x){
  ll ans=T[p].query(x);
	//cout<<ans<<endl;
	if (l==r) return ans;
  int mid=(l+r)>>1;
	if (pos<=mid) return min(ans,query(p<<1,l,mid,pos,x));
	else return min(ans,query(p<<1|1,mid+1,r,pos,x));
}
int main(){
	cnt=0;
	ll C0;
	n=read();m=read();C0=read();
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=2;i<=n;++i){
	  int type;
		type=read();
		if (type==0){
		  int fr,id;
			ll x,y,z,c;
			//scanf("%d%d%lld%lld%lld%lld",&fr,&id,&x,&y,&z,&c);
			//cout<<x<<" "<<y<<" "<<z<<" "<<c<<endl;
      fr=read();id=read();x=read();y=read();z=read();c=read();
			Pl[id].k=-2ll*x;
			Pl[id].b=x*x+c;
			Pl[id].id=id;
			fr++;
			add(fr,i);
			appear[id].push_back(i);
		}else{
		  int fr,id;
			//scanf("%d%d",&fr,&id);
			fr=read();id=read();
			fr++;
			add(fr,i);
			appear[id].push_back(i);
		}
	}
	dfs(1);
	for (int i=1;i<n;++i) Pl[i].id=i;
  sort(Pl+1,Pl+n,cmp);
	for (int i=1;i<n;++i){
	  int id=Pl[i].id;
    if (appear[id].size()==0) continue;
		sort(appear[id].begin(),appear[id].end(),cmp2);
		int head=in[appear[id][0]],tail=out[appear[id][0]];
		//cout<<head<<" "<<tail<<endl;
		//printf("insert:%d\n",appear[id][0]);
		for (int it=1;it<appear[id].size();++it)
			insert(1,1,n,head,in[appear[id][it]]-1,i),head=out[appear[id][it]]+1;
    insert(1,1,n,head,tail,i);
	}	
	for (int i=1;i<=m;++i){
	  //scanf("%d%lld",&Q[i].s,&Q[i].x);
		Q[i].s=read();
		Q[i].x=read();
		Q[i].s++;
		Q[i].id=i;
	}
	sort(Q+1,Q+m+1,cmp3);
	for (int i=1;i<=m;++i){
    //printf("query %d from %lld\n", Q[i].id, Q[i].x);	
		//cout<<query(1,1,n,in[Q[i].s],Q[i].x)<<endl;
		//printf("%lld\n",query(1,1,n,in[Q[i].s],Q[i].x));
		ans[Q[i].id]=min(query(1,1,n,in[Q[i].s],Q[i].x),C0)+Q[i].x*Q[i].x;
  }
	for (int i=1;i<=m;++i) printf("%lld\n",ans[i]);
	return 0;
}
