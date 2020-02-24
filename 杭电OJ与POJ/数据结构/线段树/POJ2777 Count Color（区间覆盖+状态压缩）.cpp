分析：
这题主要是需要想到在情况不多的情况，可以用二进制来表示颜色。二进制在acm竞赛中的运用十分灵活
==============================================
代码：
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
typedef long long ll;
const int N =1e5+10;
const int base =10000;
struct node{
	int l,r;
	int val;
	int lazy;
}tr[N<<2];
int n;
void pushup(int u){
	tr[u].val=tr[u<<1].val|tr[u<<1|1].val;
}
void pushdown(int u){
	if(tr[u].lazy){
		tr[u<<1].val=tr[u<<1|1].val=tr[u].lazy;
		tr[u<<1].lazy=tr[u<<1|1].lazy=tr[u].lazy;
		tr[u].lazy=0; 
	}
}
void build(int u,int l,int r){
	if(l==r){
		tr[u]={l,r,1,0};
	}
	else{
		tr[u]={l,r};
		int mid=l+r>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		pushup(u);
	}
}
void modify(int u,int l,int r,int x){
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].val=1<<(x-1);
		tr[u].lazy=1<<(x-1);
	}
	else{
		pushdown(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid)
		modify(u<<1,l,r,x);
		if(r>mid)
		modify(u<<1|1,l,r,x);
		pushup(u);
	}
}
int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r){
		return tr[u].val;
	}
	else{
		pushdown(u);
		int mid=tr[u].l+tr[u].r>>1;
		int res=0;
		if(l<=mid)
		res=query(u<<1,l,r);
		if(r>mid)
		res|=query(u<<1|1,l,r);
		return res;
	}
}
int check(int x){
	int i;
	int res=0;
	while(x){
		if(x&1)
		res++;
		x>>=1;
	}
	return res;
}
int main(){
	int n,t,q;
	cin>>n>>t>>q;
	build(1,1,n);
	while(q--){
		int l,r;
		char s[2];
		scanf("%s",s);
		if(*s=='C'){
			int x;
			scanf("%d%d%d",&l,&r,&x);
			if(l>r)
			swap(l,r);
			modify(1,l,r,x);
		}
		else{
			scanf("%d%d",&l,&r);
			if(l>r)
			swap(l,r);
			printf("%d\n",check(query(1,l,r)));
			
		}
	}
	return 0;
}
