#include<iostream>
#include<cstdio>
using namespace std;
#define Maxn 200000
int sz,root;//size of tree and root
namespace splay{	
	int f[Maxn];//father
	int ch[Maxn][2];//child ; 0 for left ; 1 for right
	int key[Maxn];//key
	int id[Maxn];
	int cnt[Maxn];//value
	int siz[Maxn];//size of subtree
	int rev[Maxn];//the tag of subtree
	//clear the node
	void clear(int x){
		ch[x][0]=ch[x][1]=f[x]=cnt[x]=key[x]=siz[x]=0;
	}
	//update the size
	void update(int x){
		siz[x]=cnt[x];
		if (ch[x][0]) siz[x]+=siz[ch[x][0]];
		if (ch[x][1]) siz[x]+=siz[ch[x][1]];
	}
	void down(int x){
	  if (rev[x]){
		  swap(ch[x][0],ch[x][1]);
			rev[ch[x][0]]^=1;rev[ch[x][1]]^=1;
			rev[x]=0;
		}
	}
	//retation
	void rotate(int x,int &k){
		int y=f[x],z=f[y],l,r;
		l=(ch[y][1]==x);r=l^1;
		if (y==k) k=x;
		else ch[z][ch[z][1]==y]=x;
		f[x]=z;f[y]=x;f[ch[x][r]]=y;
		ch[y][l]=ch[x][r];ch[x][r]=y;
		update(y);update(x);
	}
	//rotate until x is the root
	void splay(int x,int &k){
		while(x!=k){
			int y=f[x],z=f[y];
			if(y!=k){
				if(ch[y][0]==x^ch[z][0]==y) rotate(x,k);
				else rotate(y,k);
			}
			rotate(x,k);
		}	
	}
	//ceate a new splay node
	void create(int v){
		sz++;
		ch[sz][0]=ch[sz][1]=f[sz]=0;
		key[sz]=v;
		cnt[sz]=1;
		siz[sz]=1;
	}  
	//insert a node
	void insert(int v){
		if (!root)
			create(v),root=sz;
		else{
			int now=root,fa=0;
			while(1){
				if (key[now]==v){
			   	cnt[now]++;
					update(now);update(fa);
					splay(now,root);
					break;
				}
				fa=now;
				now=ch[fa][v>key[fa]];
				if (!now){
					create(v);
					f[sz]=fa;
					ch[fa][v>key[fa]]=sz;
					update(fa);
					splay(sz,root);
					break;
				}
			}
		}
	}
	//find x's pos
	int findpos(int v){
		int now=root,ans=0;
		while(1){
			if (v<key[now])
				now=ch[now][0];
			else{
				ans+=ch[now][0]?siz[ch[now][0]]:0;
				if (v==key[now]){
					splay(now,root);
					return ans+1;
				}
				ans+=cnt[now];
				now=ch[now][1];
			}
		}
	}
	//find pos's x
	int findx(int x){
		int now=root;
		while(1){
			down(now);
			if (ch[now][0] && x<=siz[ch[now][0]]) now=ch[now][0];
			else{
				int temp=(ch[now][0]?siz[ch[now][0]]:0)+cnt[now];
				if (x<=temp)
					return key[now];
				x-=temp;
				now=ch[now][1];
			}
		}
	}
	int pre(){
		int now=ch[root][0];
		while(ch[now][1])
			now=ch[now][1];
		return now;
	}
	int nex(){
		int now=ch[root][1];
		while(ch[now][0])
			now=ch[now][0];
		return now;
	}
	void del(int x){
		int t=findpos(x);
		if (cnt[root]>1){
			cnt[root]--;
			update(root);
			return;
		}
		//none
		if (!ch[root][0] && !ch[root][1]){
			clear(root);
			root=0;
			return;
		}
		//one
		if (!ch[root][1]){
			int temp=root;
			root=ch[root][0];
			f[root]=0;
			clear(temp);
			return;
		}
		else
		if (!ch[root][0]){
			int temp=root;
			root=ch[root][1];
			f[root]=0;
			clear(temp);
			return;
		}
		//two
		int pre1=pre(),temp=root;
		splay(pre1,root);
		f[ch[temp][1]]=root;
		ch[root][1]=ch[temp][1];
		clear(temp);
		update(root);
	}
	void reverse(int l,int r){
		int x=findx(l),y=findx(r+2);
		splay(x,root);splay(y,ch[x][1]);
		int z=ch[y][0];
		rev[z]^=1;
	}
	void build(int l,int r,int fa){
		if (l>r) return;
		int mid=(l+r)>>1,now=id[mid],last=id[fa];
		if (l==r) siz[now]=1;
		else build(l,mid-1,mid),build(mid+1,r,mid);
		key[now]=id[mid];
		cnt[now]=1;
		f[now]=last;
		update(now);
		ch[last][mid>=fa]=now;
	}
}
int main(){
	sz=0;root=0;
	int n;
	scanf("%d",&n);
	while (n--){
	  using namespace splay;
		int opt,x;
		scanf("%d%d",&opt,&x);
		switch(opt){
		  case 1:insert(x);break;
      case 2:del(x);break;
			case 3:printf("%d\n",findpos(x));break;
			case 4:printf("%d\n",findx(x));break;
			case 5:insert(x);printf("%d\n",key[pre()]);del(x);break;
			case 6:insert(x);printf("%d\n",key[nex()]);del(x);break;
		}
	}
	return 0;
}
