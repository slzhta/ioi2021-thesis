#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<ctime>
#define N 1000005
#define ll long long
using namespace std;
struct pl{int l,r,fi;}e[N*4];
int nx[22][2][N],op[22][N];
ll sum[22][N];int las[22];
struct point{int x,y,w;}s[N],si[N];
int n,m,lx,rx,ly,ry,cnt=1,tot;
int get(){
	char ch;int v=0;
	while(!isdigit(ch=getchar()));v=ch-48;
	while(isdigit(ch=getchar())) v=(v<<1)+(v<<3)+ch-48;
	return v;
}
bool cmp(const point &A,const point &B){return A.x<B.x;}
void build(int li,int ri,int no,int deep){
	if(li==ri){e[no].fi=las[deep];sum[deep][las[deep]++]=s[li].w;return;}
	int mid=(li+ri)>>1;
	e[no].l=++cnt;e[no].r=++cnt;
	build(li,mid,e[no].l,deep+1);build(mid+1,ri,e[no].r,deep+1);
	e[no].fi=las[deep];las[deep]+=(ri-li+1);
	int lt=li,rt=mid+1,tot=li,tit=e[no].fi;
	while(lt<=mid||rt<=ri){
		if(lt==mid+1){
			si[tot]=s[rt];nx[deep][1][tit]=rt-mid-1;nx[deep][0][tit]=lt-li;
			op[deep][tit++]=1;tot++;rt++;
		}
		else if(rt==ri+1){
			si[tot]=s[lt];nx[deep][1][tit]=rt-mid-1;nx[deep][0][tit]=lt-li;
			op[deep][tit++]=0;tot++;lt++;
		}
		else if(s[lt].y<s[rt].y){
			si[tot]=s[lt];nx[deep][1][tit]=rt-mid-1;nx[deep][0][tit]=lt-li;
			op[deep][tit++]=0;tot++;lt++;
		}
		else{
			si[tot]=s[rt];nx[deep][1][tit]=rt-mid-1;nx[deep][0][tit]=lt-li;
			op[deep][tit++]=1;tot++;rt++;
		}
	}
	for(int i=li;i<=ri;i++) s[i]=si[i];ll su=0;tit=e[no].fi;
	for(int i=li;i<=ri;i++) su+=s[i].w,sum[deep][tit++]=su;
	las[deep]=tit;
	/*cerr<<li<<" - "<<ri<<" : "<<no<<endl;
	for(int i=li;i<=ri;i++) cerr<<si[i].y<<" ";cerr<<endl;
	for(int i=li;i<=ri;i++) cerr<<si[i].w<<" ";cerr<<endl;
	for(int i=li;i<=ri;i++) cerr<<e[no].sum[i-li]<<" ";cerr<<endl;
	for(int i=li;i<=ri;i++) cerr<<e[no].nx[0][i-li]<<" ";cerr<<endl;
	for(int i=li;i<=ri;i++) cerr<<e[no].nx[1][i-li]<<" ";cerr<<endl;
	for(int i=li;i<=ri;i++) cerr<<e[no].op[i-li]<<" ";cerr<<endl;*/
}
ll find(int li,int ri,int no,int mb1,int mb2,int lt,int rt,int deep){
	//cerr<<"find:"<<li<<" - "<<ri<<" - "<<lt<<" : "<<rt<<" "<<mb1<<" "<<mb2<<" "<<s[li].x<<" "<<s[ri].x<<endl;
	tot++;
	if(s[li].x>mb2||s[ri].x<mb1) return 0;
	if(lt<0) lt=0;if(rt>ri-li) rt=ri-li; 
	if(lt>rt) return 0;lt+=e[no].fi;rt+=e[no].fi;
	if(s[li].x>=mb1&&s[ri].x<=mb2){
		//cerr<<"in:"<<lt<<" - "<<rt<<endl;
		//if(lt!=0) cerr<<e[no].sum[rt]<<" "<<e[no].sum[lt-1]<<endl;
		if(lt==e[no].fi) return sum[deep][rt];
		else return sum[deep][rt]-sum[deep][lt-1];
	}
	int mid=(li+ri)>>1;
	int lp=nx[deep][0][lt],rp=nx[deep][0][rt];
	if(op[deep][rt]==1) rp--;ll ans=find(li,mid,e[no].l,mb1,mb2,lp,rp,deep+1);
	lp=nx[deep][1][lt];rp=nx[deep][1][rt];
	//if(li==1&&ri==5) cerr<<lp<<" --- "<<rp<<" !!!! "<<no<<" "<<lt<<" - "<<rt<<endl; 
	if(op[deep][rt]==0) rp--;ans+=find(mid+1,ri,e[no].r,mb1,mb2,lp,rp,deep+1); 
	return ans;
}
int get_lower(int a){
	int li=1,ri=n+1;
	while(li+1<ri){
		int mid=(li+ri)>>1;
		if(si[mid].y>=a) ri=mid;else li=mid; 
	}
	if(si[li].y>=a) return li;return ri;
}
int main()
{
	srand(1313123);int mb=10000;
	freopen("find.in","r",stdin);
	freopen("find.out","w",stdout);
	n=get();m=get();
	for(int i=1;i<=n;i++) s[i].x=get(),s[i].y=get(),s[i].w=get();
	cerr<<clock()<<endl;
	sort(s+1,s+1+n,cmp);build(1,n,1,1);
	sort(s+1,s+1+n,cmp);ll allans=0;
	cerr<<clock()<<endl;
	//for(int i=1;i<=n;i++) cerr<<si[i].y<<" - ";cerr<<endl;
	for(int i=1;i<=m;i++){
		//lx=get();ly=get();rx=get();ry=get();
		int lx=rand()%mb+1,rx=rand()%mb+1,ly=rand()%mb+1,ry=rand()%mb+1;
		if(lx>rx) swap(lx,rx);if(ly>ry) swap(ly,ry);
		int lt=get_lower(ly),rt=get_lower(ry+1)-1;
		//cerr<<lt<<" --- "<<rt<<endl;
		//if(lt>rt) puts("0");
		//else printf("%lld\n",find(1,n,1,lx,rx,lt-1,rt-1));
		ll ans=find(1,n,1,lx,rx,lt-1,rt-1,1);allans^=ans;
	}
	printf("%lld\n",allans);
	cerr<<clock()<<" : "<<tot<<endl;
	return 0;
}
