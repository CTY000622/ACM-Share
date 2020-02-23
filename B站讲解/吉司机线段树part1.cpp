HDU5306 Gorgeous Sequence

#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>
#include<string>
#include<cstring>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
const int N=1e6+10;
struct node{
    int l,r;
    ll cnt;
    ll sum;
    ll ma;
    ll se;
}tr[N<<2];
int a[N];
void pushup(int u){
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
    tr[u].cnt=0;
    tr[u].ma=max(tr[u<<1].ma,tr[u<<1|1].ma);
    if(tr[u<<1].ma==tr[u<<1|1].ma){
        tr[u].se=max(tr[u<<1].se,tr[u<<1|1].se);
        tr[u].cnt=tr[u<<1|1].cnt+tr[u<<1].cnt;
    }
    else{
        tr[u].se=max(tr[u<<1].se,tr[u<<1|1].se);
        tr[u].cnt=tr[u<<1].ma>tr[u<<1|1].ma?tr[u<<1].cnt:tr[u<<1|1].cnt;
        if(tr[u<<1].ma>tr[u<<1|1].ma)
        tr[u].se=max(tr[u].se,tr[u<<1|1].ma);
        else
        tr[u].se=max(tr[u].se,tr[u<<1].ma);
    }
}
void pushdown(int u){
    if(tr[u<<1].ma>tr[u].ma){
        tr[u<<1].sum-=(tr[u<<1].ma-tr[u].ma)*tr[u<<1].cnt;
        tr[u<<1].ma=tr[u].ma;
    }
    
    if(tr[u<<1|1].ma>tr[u].ma){
        tr[u<<1|1].sum-=(tr[u<<1|1].ma-tr[u].ma)*tr[u<<1|1].cnt;
        tr[u<<1|1].ma=tr[u].ma;
    }
    
}
void build(int u,int l,int r){
    if(l==r){
        tr[u]={l,r,1,a[l],a[l],-1};
    }
    else{
        tr[u]={l,r};
        tr[u].se=-1;
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
void modify(int u,int l,int r,int x){
    if(x>tr[u].ma)
    return ;
    if(tr[u].l>=l&&tr[u].r<=r&&x>tr[u].se){
        tr[u].sum-=(tr[u].ma-x)*tr[u].cnt;
        tr[u].ma=x;
        return ;
    }
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid)
    modify(u<<1,l,r,x);
    if(r>mid)
    modify(u<<1|1,l,r,x);
    pushup(u);
}
int query1(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r)
    return tr[u].ma;
    int mid=tr[u].l+tr[u].r>>1;
    pushdown(u);
    int res=0;
    if(l<=mid)
    res=query1(u<<1,l,r);
    if(r>mid)
    res=max(res,query1(u<<1|1,l,r));
    return res;
}
ll query2(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r)
    return tr[u].sum;
    int mid=tr[u].l+tr[u].r>>1;
    pushdown(u);
    ll res=0;
    if(l<=mid)
    res=query2(u<<1,l,r);
    if(r>mid)
    res+=query2(u<<1|1,l,r);
    return res;
}
int main(){
    int t;
    int n,m;
    cin>>t;
    while(t--){
        scanf("%d%d",&n,&m);
        int i;
        for(i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }    
        build(1,1,n);
        while(m--){
            int opt;
            int l,r;
            int x;
            scanf("%d",&opt);
            if(opt==0){
                scanf("%d%d%d",&l,&r,&x);
                modify(1,l,r,x);
            }
            else if(opt==1){
                scanf("%d%d",&l,&r);
                printf("%lld\n",query1(1,l,r));
            }
            else{
                scanf("%d%d",&l,&r);
                printf("%lld\n",query2(1,l,r));
            }
        }
    }
    return 0;    
}
