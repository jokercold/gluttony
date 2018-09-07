#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define ull unsigned long long
#define N 200000
char ch[N];
char d[20];
int root,sz;
int h[N];
ull radix[N];
namespace Splay{
	 int ch[N][2],f[N],siz[N];
	 ull v[N];
	 ull hash[N];
   void update(int x){
	   int l=ch[x][0],r=ch[x][1];
		 siz[x]=siz[l]+siz[r]+1;
		 hash[x]=hash[l]+radix[siz[l]]*v[x]+radix[siz[l]+1]*hash[r];
	 }
	 void rotate(int x,int &k){
	   int y=f[x],z=f[y];
		 int l=(ch[y][1]==x),r=l^1;
		 if (y==k) k=x;
		 else ch[z][ch[z][1]==y]=x;
		 f[x]=z;f[y]=x;f[ch[x][r]]=y;
		 ch[y][l]=ch[x][r];ch[x][r]=y;
		 update(y);update(x);
	 }
	 void splay(int x,int &k){
	   while (x!=k){
		   int y=f[x],z=f[y];
			 if (y!=k){
			   if (ch[y][0]==x^ch[z][0]==y) rotate(x,k);
				 else rotate(y,k);
			 }
			 //cout<<x<<" "<<y<<" "<<z<<endl;
			 rotate(x,k);
		 }
	 }
	 int find(int x){
	   int now=root;
		 while (now){
		   if (ch[now][0]&&siz[ch[now][0]]>=x) now=ch[now][0];
			 else{
			   int temp=((ch[now][0])?siz[ch[now][0]]:0)+1;
				 if (temp>=x) return now;
	       x-=temp;
				 now=ch[now][1];
			 }
		 }
	 }
	 ull query(int l,int r){
	   int x=find(l),y=find(r+2);
		 //cout<<"YES"<<endl;
		 //cout<<x<<" "<<y<<endl;
		 splay(x,root);splay(y,ch[x][1]);
		 //cout<<"YES"<<endl;
		 int z=ch[y][0];
		 //cout<<x<<" "<<y<<" "<<v[z]<<" "<<hash[z]<<endl;
		 //cout<<hash[z]<<endl;
		 return hash[z];
	 }
	 int LCQ(int x,int y){
	   int l=0,r=sz-y-1,ans=0;
		 while (l<=r){
			 //cout<<l<<" "<<r<<endl;
		   int mid=(l+r)>>1;
			 if (query(x,x+mid-1)==query(y,y+mid-1)) l=mid+1,ans=mid;
			 else r=mid-1;
		 }
		 return ans;
	 }
	 void change(int l,int vv){
	   int x=find(l),y=find(l+2);
		 splay(x,root);splay(y,ch[x][1]);
		 int z=ch[y][0];
		 v[z]=vv;
		 siz[z]=1;
		 hash[z]=vv;
     update(y);update(x);
	 }
	 void insert(int l,int vv){
	   int x=find(l+1),y=find(l+2);
		 splay(x,root);splay(y,ch[x][1]);
		 //cout<<x<<" "<<y<<endl;
		 ++sz;
		 ch[y][0]=sz;
		 f[sz]=y;
		 siz[sz]=1;
		 v[sz]=vv;
		 hash[sz]=vv;
		 update(y);update(x);
	 }
	 void build(int l,int r,int fa){
	   if (l>r) return;
		 int mid=(l+r)>>1;
		 if (l==r){
		   hash[l]=v[l]=h[l];
			 siz[l]=1;
		 }else build(l,mid-1,mid),build(mid+1,r,mid);
		 f[mid]=fa;
		 v[mid]=h[mid];
		 //cout<<mid<<" "<<v[mid]<<endl;
		 update(mid);
		 ch[fa][mid>=fa]=mid;
	 }
}
int main(){
	radix[0]=1;
	for (int i=1;i<=150005;++i) radix[i]=radix[i-1]*233;
	scanf("%s",ch+2);
  int n=strlen(ch+2);
	for (int i=2;i<=n+1;++i) h[i]=ch[i]-'a';
	h[1]=1<<29;h[n+2]=1<<29;
	Splay::build(1,n+2,0);
	sz=n+2;
	root=(n+3)>>1;
	//cout<<"YES"<<endl;
	int m;
	scanf("%d",&m);
  while (m--){
	  scanf("%s",ch);
		//cout<<m<<endl;
		if (ch[0]=='Q'){
		  int x,y;
			scanf("%d%d",&x,&y);
			if (x>y) swap(x,y);
			printf("%d\n",Splay::LCQ(x,y));
		}
		if (ch[0]=='R'){
		  int x;
			scanf("%d",&x);
			scanf("%s",d);
      Splay::change(x,d[0]-'a');
		}
		if (ch[0]=='I'){
		  int x;
			scanf("%d",&x);
			scanf("%s",d);
			Splay::insert(x,d[0]-'a');
		}
	}
	return 0;
}
