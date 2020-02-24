分析：
我们知道如何维护一维子段和，那么二维也是一样的，只需要枚举下边界，在不断往上枚举上边界遍历所有情况即可，矩阵和其实相当于把第二维和第一维压缩到一维即可
=================================================
代码：
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector> 
using namespace std;
typedef long long ll;
const int N=1e5+10;
const int inf=0x3f3f3f3f;
vector<int> xi;
vector<int> yi;
struct node{
	int l,r;
	ll sum;
	ll tsum;
	ll lsum;
	ll rsum;
}tr[N<<2];
struct qi{
	int x,y;
	ll w;
}q[N];
bool cmp(qi a,qi b){
	if(a.y==b.y)
	return a.x<b.x;
	return a.y<b.y; 
}
void build(int u,int l,int r){
	if(l==r){
		tr[u]={l,l};
	}
	else{
		tr[u]={l,r};
		int mid=l+r>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
	}
}
int findy(int x){
	return lower_bound(yi.begin(),yi.end(),x)-yi.begin()+1;
}
int findx(int x){
	return lower_bound(xi.begin(),xi.end(),x)-xi.begin()+1;
}
void pushup(int u){
	tr[u].lsum=max(tr[u<<1].lsum,tr[u<<1].sum+tr[u<<1|1].lsum);
	tr[u].rsum=max(tr[u<<1|1].rsum,tr[u<<1|1].sum+tr[u<<1].rsum);
	tr[u].tsum=max(max(tr[u<<1].tsum,tr[u<<1|1].tsum),tr[u<<1].rsum+tr[u<<1|1].lsum);
	tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
void modify(int u,int w,ll x){
	if(tr[u].l==tr[u].r){
		tr[u].lsum=tr[u].sum=tr[u].rsum=tr[u].tsum=tr[u].sum+x;
		return ;
	}
	else{
		int mid=tr[u].l+tr[u].r>>1;
		if(w<=mid)
		modify(u<<1,w,x);
		else
		modify(u<<1|1,w,x);
		pushup(u);
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		int i;
		cin>>n;
		xi.clear();
		yi.clear();
		for(i=1;i<=n;i++){
			scanf("%d%d%lld",&q[i].x,&q[i].y,&q[i].w);
			xi.push_back(q[i].x);
			yi.push_back(q[i].y);
		}
		sort(q+1,q+n+1,cmp);
		sort(xi.begin(),xi.end());
		xi.erase(unique(xi.begin(),xi.end()),xi.end());
		sort(yi.begin(),yi.end());
		yi.erase(unique(yi.begin(),yi.end()),yi.end());
		int nx=xi.size();
		int ny=yi.size();
		int now=1;
		int k;
		ll ans=0;
		for(i=1;i<=ny;i++){  //枚举下边界 
			build(1,1,nx);
			for(int j=i,k=now;j<=ny;j++){ //上边界 				
			
				while(k<=n&&findy(q[k].y)==j){
					modify(1,findx(q[k].x),q[k].w);
					k++;
				}		
				if(j==i)
				now=k;
				ans=max(ans,tr[1].tsum);

			}
		}
		cout<<ans<<endl;
	}
}
