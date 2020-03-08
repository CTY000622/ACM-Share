分析：
这道题和poj1823 一毛一样
可以参考我的另一个题解
唯一的区别是，他要找的是最左边的，那么我们自然可以考虑越左越好
如果当前点的lmax能满足，直接返回
不然的话，如果当前点的左儿子的tmax满足，就去左节点
如果是横跨区间的，也直接返回
如果在右儿子，就去右儿子
注意，我之前已经特判过不满足的情况，所以一旦进入，就一定满足。
==================================
代码：
#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1e6+10;
const int inf=0x3f3f3f3f;
struct node{
    int l,r;
    int lazy;
    int tmax;
    int lmax;
    int rmax;
}tr[N];
void pushup(int u){
    tr[u].rmax=tr[u<<1|1].rmax;
    if(tr[u<<1|1].lazy==-1)
        tr[u].rmax+=tr[u<<1].rmax;
    tr[u].lmax=tr[u<<1].lmax;
    if(tr[u<<1].lazy==-1)
        tr[u].lmax+=tr[u<<1|1].lmax;
    tr[u].tmax=max(tr[u<<1].rmax+tr[u<<1|1].lmax,max(tr[u<<1].tmax,tr[u<<1|1].tmax));
    if(tr[u<<1].lazy==tr[u<<1|1].lazy)
        tr[u].lazy=tr[u<<1].lazy;
    else{
        tr[u].lazy=0;
    }
}
void build(int u,int l,int r){
    if(l==r){
        tr[u]=(node){l,l,-1,1,1,1};
    }
    else{
        tr[u]=(node){l,r,-1};
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
void pushdown(int u){
    tr[u<<1].lazy=tr[u<<1|1].lazy=tr[u].lazy;
    if(tr[u].lazy==1){
        tr[u<<1].lmax=tr[u<<1].rmax=tr[u<<1].tmax=0;
        tr[u<<1|1].lmax=tr[u<<1|1].rmax=tr[u<<1|1].tmax=0;
    }
    else{
        tr[u<<1].lmax=tr[u<<1].rmax=tr[u<<1].tmax=tr[u<<1].r-tr[u<<1].l+1;
        tr[u<<1|1].lmax=tr[u<<1|1].rmax=tr[u<<1|1].tmax=tr[u<<1|1].r-tr[u<<1|1].l+1;
    }
    tr[u].lazy=0;
}
void modify(int u,int l,int r,int x){
    if(tr[u].l>=l&&tr[u].r<=r){
        tr[u].lazy=x;
        if(x==1){
            tr[u].lmax=tr[u].rmax=tr[u].tmax=0;
        }
        else{
            tr[u].lmax=tr[u].rmax=tr[u].tmax=tr[u].r-tr[u].l+1;
        }
        return ;
    }
    if(tr[u].lazy!=0)
        pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid)
        modify(u<<1,l,r,x);
    if(r>mid){
        modify(u<<1|1,l,r,x);
    }
    pushup(u);
}
int query(int u,int k){
    if(tr[u].lmax>=k)
        return tr[u].l;
    if(tr[u<<1].tmax>=k)
        return query(u<<1,k);
    if(tr[u<<1].rmax+tr[u<<1|1].lmax>=k)
        return tr[u<<1].r-tr[u<<1].rmax+1;
    return query(u<<1|1,k);
}
int main(){
    int n,m;
    cin>>n>>m;
    build(1,1,n);
    int i;
    for(i=1;i<=m;i++){
        int c;
        scanf("%d",&c);
        if(c==1){
            int k;
            scanf("%d",&k);
            if(tr[1].tmax<k){
                printf("0\n");
                continue;
            }
            int tmp=query(1,k);
            printf("%d\n",tmp);
            modify(1,tmp,tmp+k-1,1);
        }
        else{
            int l,r;
            scanf("%d%d",&l,&r);
            modify(1,l,l+r-1,-1);
        }
    }

}
