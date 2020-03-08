分析：
这道题主要是第三问较为复杂，但是我们曾经学过求一维上的最大子段和，这样自然想到设计lmax，rmax和tmax来表示最长连续的0
然后本题的懒标记可以设计为三种状态，但是在传递的时候只需当当前是全空和全满的时候传递，不然这个传递没有意义，传递下去就是为了更改子节点，如果当前父节点都是有空又满
那么只需要在更新的时候更新当前状态即可。
在poj中需要用g++交，因为我的代码中c++由于poj的环境太差，会编译错误
===================================================
#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1e5+10;
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
int main(){
    int n,p;
    cin>>n>>p;
    build(1,1,n);
    int i;
    int c;
    for(i=0;i<p;i++){
        scanf("%d",&c);
        if(c==1){
            int l,len;
            scanf("%d%d",&l,&len);
            int r=l+len-1;
            modify(1,l,r,1);
        }
        else if(c==2){
            int l,len;
            scanf("%d%d",&l,&len);
            int r=l+len-1;
            modify(1,l,r,-1);
        }
        else{
            printf("%d\n",tr[1].tmax);
        }
    }
}
