#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 60000
#define ll long long
#define lowbit(x) ((x)&(-x))
int n,m;
struct node{
  ll h[N];
  node(){memset(h,0,sizeof(h));}
	void add(int x,int z){
	  for (int i=x;i<=N;i+=lowbit(i)) h[i]+=z; 
	}
  ll sum(int x){
		int ans=0;
	  for (int i=x;i>0;i-=lowbit(i)) ans+=h[i]; 
	  return ans;
	}
}C1,C2;
ll totalsum(int x){
  return C1.sum(x)*(x+1)-C2.sum(x);
}
struct yh{
  int q,a,b,c,id;
}Q[N],New[N];
int ans[N];
bool Count[N];
void cdq(int L,int R,int l,int r){
  //cout<<L<<" "<<R<<" "<<l<<" "<<r<<endl;
	if (L>R) return;
	if (l>r) return;
	if (l==r){
	  for (int i=L;i<=R;++i)
		if (Q[i].q==2) ans[Q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1;
	//cout<<mid<<"::::::::"<<endl;
	int l1=L-1,l2=R+1;
	for (int i=L;i<=R;++i)
	if (Q[i].q==1){
	  if (Q[i].c>mid){
		  C1.add(Q[i].a,1);C1.add(Q[i].b+1,-1);
			C2.add(Q[i].a,Q[i].a);C2.add(Q[i].b+1,-Q[i].b-1);
		  --l2;New[l2]=Q[i];
		}else ++l1,New[l1]=Q[i];
	}else{
	  ll he=totalsum(Q[i].b)-totalsum(Q[i].a-1);
		//cout<<he<<endl;
    if (he<Q[i].c){
		  Q[i].c-=he;
			++l1;New[l1]=Q[i];
		}else --l2,New[l2]=Q[i];
	}
	//cout<<L<<" "<<R<<"------------------"<<l1<<" "<<l2<<endl;
	reverse(New+l2,New+R+1);
	for (int i=L;i<=R;++i){
	  Q[i]=New[i];
		if (Q[i].q==1&&Q[i].c>mid){
		  C1.add(Q[i].a,-1);C1.add(Q[i].b+1,1);
			C2.add(Q[i].a,-Q[i].a);C2.add(Q[i].b+1,Q[i].b+1);
		}
	}
	//cout<<L<<" "<<R<<"------------------"<<l1<<" "<<l2<<endl;
	cdq(L,l1,l,mid);
	cdq(l2,R,mid+1,r);
}
int main(){
	scanf("%d%d",&n,&m);
  for (int i=1;i<=m;++i){
		scanf("%d%d%d%d",&Q[i].q,&Q[i].a,&Q[i].b,&Q[i].c);
	  Q[i].id=i;
		if (Q[i].q==2) Count[i]=true;
	}
	cdq(1,m,-n,n);
	for (int i=1;i<=m;++i)
	if (Count[i]) printf("%d\n",ans[i]);
	return 0;
}
