#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<ctime>
#define N 1000005
#define inf 1e6
#define ll long long
using namespace std;
int n,m,cnt=1,lx,ly,rx,ry,tot;ll ans;
struct point{int x,y,w;}s[N];
struct pl{int l,r,root;ll sum;}e[N*60];
int get(){
	char ch;int v=0;
	while(!isdigit(ch=getchar()));v=ch-48;
	while(isdigit(ch=getchar())) v=(v<<1)+(v<<3)+ch-48;
	return v;
}
void build(int li,int ri,int no,int mb,int id,int op){
	if(li>mb||ri<mb) return;
	if(op==0){
		if(e[no].root==0) e[no].root=++cnt;
		build(1,inf,e[no].root,s[id].y,id,1);
	}
	else e[no].sum+=s[id].w;
	if(li==ri) return;
	int mid=(li+ri)>>1;
	if(mb<=mid){
		if(e[no].l==0) e[no].l=++cnt;
		build(li,mid,e[no].l,mb,id,op);
	}
	else{
		if(e[no].r==0) e[no].r=++cnt;
		build(mid+1,ri,e[no].r,mb,id,op);
	}
}
void find(int li,int ri,int no,int mb1,int mb2,int op){
	tot++;
	if(no==0) return;if(li>mb2||ri<mb1) return;
	if(li>=mb1&&ri<=mb2){
		if(op==0) find(1,inf,e[no].root,ly,ry,1);
		else ans+=e[no].sum;
		return;
	}
	int mid=(li+ri)>>1;
	find(li,mid,e[no].l,mb1,mb2,op);find(mid+1,ri,e[no].r,mb1,mb2,op);
}
int main()
{
	srand(1313123);int mb=10000;
	freopen("find.in","r",stdin);
	freopen("find.ans","w",stdout);
	n=get();m=get();
	for(int i=1;i<=n;i++) s[i].x=get(),s[i].y=get(),s[i].w=get(); 
	cerr<<clock()<<endl;
	for(int i=1;i<=n;i++) build(1,inf,1,s[i].x,i,0);
	ll allans=0;
	cerr<<clock()<<" : "<<cnt<<endl;
	for(int i=1;i<=m;i++){
		lx=rand()%mb+1,rx=rand()%mb+1,ly=rand()%mb+1,ry=rand()%mb+1;
		if(lx>rx) swap(lx,rx);if(ly>ry) swap(ly,ry);
		find(1,inf,1,lx,rx,0);allans^=ans;
	}
	printf("%lld\n",allans);
	cerr<<clock()<<" : "<<tot<<endl;
	return 0;
}
