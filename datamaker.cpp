#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<ctime>
#define N 10000005
#define rand() ((rand()<<15)|rand()) 
using namespace std;
int main()
{
	srand(time(0));
	freopen("find.in","w",stdout);
	int n=200000,mb=10000,m=1000000;cout<<n<<" "<<m<<endl;
	for(int i=1;i<=n;i++) cout<<rand()%mb+1<<" "<<rand()%mb+1<<" "<<rand()%mb+1<<endl;
	for(int i=1;i<=m;i++){
		int lx=rand()%mb+1,rx=rand()%mb+1,ly=rand()%mb+1,ry=rand()%mb+1;
		if(lx>rx) swap(lx,rx);if(ly>ry) swap(ly,ry);
		//cout<<lx<<" "<<ly<<" "<<rx<<" "<<ry<<endl;
	}
	return 0;
}
