#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<ctime>
#define ll long long
#define N 1000005 
using namespace std;
int n,m,lx,ly,rx,ry,root,tot;
struct point{int x,y,w,l,r;ll sum;int mix,mxx,miy,mxy;}s[N];
int get(){
	char ch;int v=0;
	while(!isdigit(ch=getchar()));v=ch-48;
	while(isdigit(ch=getchar())) v=(v<<1)+(v<<3)+ch-48;
	return v;
}
bool cmp1(const point &A,const point &B){return A.x<B.x;}
bool cmp2(const point &A,const point &B){return A.y<B.y;}
int build(int li,int ri,int op){
	if(li>ri) return 0;
	if(li==ri){
		s[li].sum=s[li].w;s[li].mix=s[li].mxx=s[li].x;
		s[li].miy=s[li].mxy=s[li].y;return li;
	}
	if(op==0) sort(s+li,s+ri+1,cmp1);else sort(s+li,s+ri+1,cmp2);
	int mid=(li+ri)>>1;
	s[mid].l=build(li,mid-1,op^1);s[mid].r=build(mid+1,ri,op^1);
	s[mid].sum=s[s[mid].l].sum+s[s[mid].r].sum+s[mid].w;
	s[mid].mix=s[mid].mxx=s[mid].x;s[mid].miy=s[mid].mxy=s[mid].y;
	for(int i=li;i<=ri;i++) s[mid].mix=min(s[mid].mix,s[i].x),s[mid].miy=min(s[mid].miy,s[i].y),
							s[mid].mxx=max(s[mid].mxx,s[i].x),s[mid].mxy=max(s[mid].mxy,s[i].y);
	return mid;
}
bool check_in(int a){return (s[a].mix>=lx)&&(s[a].miy>=ly)&&(s[a].mxx<=rx)&&(s[a].mxy<=ry);}
bool check(int a){return (s[a].x>=lx)&&(s[a].x<=rx)&&(s[a].y>=ly)&&(s[a].y<=ry);}
bool check_out(int a){return (s[a].mix>rx)||(s[a].mxx<lx)||(s[a].miy>ry)||(s[a].mxy<ly);}
ll find(int a){
	tot++;
	if(a==0) return 0;
	if(check_out(a)) return 0;
	if(check_in(a)) return s[a].sum;
	ll sum=0;if(check(a)) sum=s[a].w;
	sum+=find(s[a].l)+find(s[a].r);
	return sum; 
}
int main()
{
	srand(1313123);int mb=10000;
	freopen("find.in","r",stdin);
	freopen("find.ans","w",stdout);
	n=get();m=get(); 
	for(int i=1;i<=n;i++) s[i].x=get(),s[i].y=get(),s[i].w=get();
	cerr<<clock()<<endl;
	root=build(1,n,0);ll allans=0;
	cerr<<clock()<<endl;
	for(int i=1;i<=m;i++){
		//lx=get();ly=get();rx=get();ry=get();
		lx=rand()%mb+1,rx=rand()%mb+1,ly=rand()%mb+1,ry=rand()%mb+1;
		if(lx>rx) swap(lx,rx);if(ly>ry) swap(ly,ry);
		ll ans=find(root);allans^=ans;
		//printf("%lld\n",ans);
	}
	printf("%lld\n",allans);
	cerr<<clock()<<" "<<tot<<endl;
	return 0;
}
