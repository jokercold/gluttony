#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,4,9,25,49};
char ss[100];
int main(){
  int cnt=0;
	for (int i=0;i<19;++i){
	  printf("%d\n",p[i]);
		fflush(stdout);
		scanf("%s",ss);
		if (!strcmp(ss,"yes")) ++cnt;
	}
	if (cnt>=2) printf("composite\n");
	else printf("prime\n");
	fflush(stdout);
	return 0;
}
