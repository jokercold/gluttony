#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){
  char last='+',ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') last='-';ch=getchar();}
	int tmp=0;
	while (ch>='0'&&ch<='9'){tmp=tmp*10+ch-'0';ch=getchar();}
	if (last=='-') tmp=-tmp;
	return tmp;
}
char ss[50];
#define db double
struct node{
  db maxx,a,b;
}t[250000];
db cal(int x,db a,db b){
  return (db)a*(x-1)+b;
}
db query(int p,int l,int r,int x){
  db ans=cal(x,t[p].a,t[p].b);
  //cout<<ans<<endl;
	if (l==r) return max(ans,t[p].maxx);
	int mid=(l+r)>>1;
	if (x<=mid) return max(ans,query(p<<1,l,mid,x));
	else return max(ans,query(p<<1|1,mid+1,r,x));
}
void change(int p,int l,int r,db a,db b){
  int mid=(l+r)>>1;
	int fl=(cal(l,t[p].a,t[p].b)<cal(l,a,b));
 	int fr=(cal(r,t[p].a,t[p].b)<cal(r,a,b));
	int fm=(cal(mid,t[p].a,t[p].b)<cal(mid,a,b));
	//cout<<fl<<" "<<fm<<" "<<fr<<endl;
	if (fl&&fr&&fm){
	  t[p].a=a;
		t[p].b=b;
		t[p].maxx=max(t[p].maxx,max(cal(l,a,b),cal(r,a,b)));
		//cout<<t[p].maxx<<endl;
		return;
	}
	if (!(fl|fr|fm)) return;
	if (fm){
	  if (fr) change(p<<1,l,mid,t[p].a,t[p].b);
		else change(p<<1|1,mid+1,r,t[p].a,t[p].b);
		t[p].a=a;
		t[p].b=b;
		t[p].maxx=max(t[p].maxx,max(cal(l,a,b),cal(r,a,b)));
	}
	if (!fm){
	  if (!fr) change(p<<1,l,mid,a,b);
		else change(p<<1|1,mid+1,r,a,b);
	}
	t[p].maxx=max(t[p].maxx,max(t[p<<1].maxx,t[p<<1|1].maxx));
}
int main(){
  int n;
	n=read();
	for (int i=1;i<=n;++i){
	  scanf("%s",ss);
		if (ss[0]=='Q'){
		  int T;
			T=read();
			int k=query(1,1,50000,T);			
			printf("%d\n",(k/100));
		}else{
		  db S,P;
			scanf("%lf%lf",&S,&P);
			change(1,1,50000,P,S);
		}
	}
	return 0;
}
