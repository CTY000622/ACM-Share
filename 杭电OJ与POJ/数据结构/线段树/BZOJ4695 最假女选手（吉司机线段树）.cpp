代码：
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
const int N=5e5+10;
const int inf=0x3f3f3f3f;
int a[N];
struct node{
    int l,r;
    int ma;
    int se;
    int mi;
    int si;
    int cnt1;
    int cnt2;
    int lazy;
    ll sum; 
}tr[N<<2];
inline void pushup(int u){
  int l=u<<1,r=u<<1|1;tr[u].sum=tr[l].sum+tr[r].sum;
  if(tr[l].ma==tr[r].ma) tr[u].ma=tr[l].ma,tr[u].cnt1=tr[l].cnt1+tr[r].cnt1,tr[u].se=max(tr[l].se,tr[r].se);
  else{
    if(tr[l].ma>tr[r].ma) swap(l,r);tr[u].ma=tr[r].ma; tr[u].cnt1=tr[r].cnt1;tr[u].se=max(tr[r].se,tr[l].ma);
  }
  if(tr[l].mi==tr[r].mi)
    tr[u].mi=tr[l].mi,tr[u].cnt2=tr[l].cnt2+tr[r].cnt2,tr[u].si=min(tr[l].si,tr[r].si);
  else{
    if(tr[l].mi<tr[r].mi) swap(l,r);tr[u].mi=tr[r].mi; tr[u].cnt2=tr[r].cnt2;tr[u].si=min(tr[r].si,tr[l].mi);
  }
}
void build(int u,int l,int r){
    if(l==r){
        tr[u]={l,r,a[l],-inf,a[l],inf,1,1,0,a[l]};
    }
    else{
        tr[u]={l,r};
        tr[u].se=-inf;
        tr[u].si=inf;
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
void pushdown(int u){
    if(tr[u].lazy){
        int p=tr[u].lazy;
        tr[u<<1].sum+=1ll*(tr[u<<1].r-tr[u<<1].l+1)*tr[u].lazy;
        tr[u<<1|1].sum+=1ll*(tr[u<<1|1].r-tr[u<<1|1].l+1)*tr[u].lazy;
        tr[u<<1].lazy+=tr[u].lazy;
        tr[u<<1|1].lazy+=tr[u].lazy;
        tr[u<<1].ma+=p,tr[u<<1].mi+=p,tr[u<<1].se+=p,tr[u<<1].si+=p;
        tr[u<<1|1].ma+=p,tr[u<<1|1].mi+=p,tr[u<<1|1].se+=p,tr[u<<1|1].si+=p;
        tr[u].lazy=0;
    }
    if(tr[u<<1].ma>tr[u].ma){
        if(tr[u<<1].mi==tr[u<<1].ma) tr[u<<1].mi=tr[u].ma;
        if(tr[u<<1].si==tr[u<<1].ma) tr[u<<1].si=tr[u].ma;
        tr[u<<1].sum-=1ll*(tr[u<<1].ma-tr[u].ma)*tr[u<<1].cnt1;
        tr[u<<1].ma=tr[u].ma;
    }
    if(tr[u<<1|1].ma>tr[u].ma){
        if(tr[u<<1|1].mi==tr[u<<1|1].ma) tr[u<<1|1].mi=tr[u].ma;
        if(tr[u<<1|1].si==tr[u<<1|1].ma) tr[u<<1|1].si=tr[u].ma;
        tr[u<<1|1].sum-=1ll*(tr[u<<1|1].ma-tr[u].ma)*tr[u<<1|1].cnt1;
        tr[u<<1|1].ma=tr[u].ma;
    }
    if(tr[u<<1].mi<tr[u].mi){
        if(tr[u<<1].ma==tr[u<<1].mi) tr[u<<1].ma=tr[u].mi;
        if(tr[u<<1].se==tr[u<<1].mi) tr[u<<1].se=tr[u].mi;
        tr[u<<1].sum-=1ll*(tr[u<<1].mi-tr[u].mi)*tr[u<<1].cnt2;
        tr[u<<1].mi=tr[u].mi;
    }
    if(tr[u<<1|1].mi<tr[u].mi){
        if(tr[u<<1|1].ma==tr[u<<1|1].mi) tr[u<<1|1].ma=tr[u].mi;
        if(tr[u<<1|1].se==tr[u<<1|1].mi) tr[u<<1|1].se=tr[u].mi;
        tr[u<<1|1].sum-=1ll*(tr[u<<1|1].mi-tr[u].mi)*tr[u<<1|1].cnt2;
        tr[u<<1|1].mi=tr[u].mi;
    }
}
void add(int u,int l,int r,int x){
    if(tr[u].l>=l&&tr[u].r<=r){
        tr[u].sum+=1ll*(tr[u].r-tr[u].l+1)*x;
        tr[u].ma+=x,tr[u].se+=x,tr[u].mi+=x,tr[u].si+=x;  //记得更改区间状态 
        tr[u].lazy+=x;
        return ;
    }
    pushdown(u);
     int mid=tr[u].l+tr[u].r>>1;
     if(l<=mid)
     add(u<<1,l,r,x);
     if(r>mid)
     add(u<<1|1,l,r,x);
     pushup(u);
}
void modify(int u,int l,int r,int x){
    if(tr[u].mi>=x)
    return ;
    if(tr[u].l>=l&&tr[u].r<=r&&tr[u].si>x){
        if(tr[u].ma==tr[u].mi) tr[u].ma=x;  //别忘了如果只有两个数或者只有一种数的情况 
        if(tr[u].se==tr[u].mi) tr[u].se=x;
        tr[u].sum+=1ll*(x-tr[u].mi)*tr[u].cnt2;
        tr[u].mi=x;
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
void change(int u,int l,int r,int x){
    if(tr[u].ma<=x)
    return ;
    if(tr[u].l>=l&&tr[u].r<=r&&tr[u].se<x){
        if(tr[u].mi==tr[u].ma) tr[u].mi=x;
        if(tr[u].si==tr[u].ma) tr[u].si=x;
        tr[u].sum+=1ll*(x-tr[u].ma)*tr[u].cnt1;
        tr[u].ma=x;
        return ;
    }
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid)
    change(u<<1,l,r,x);
    if(r>mid)
    change(u<<1|1,l,r,x);
    pushup(u);
} 
ll query(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r)
    return tr[u].sum;
    int mid=tr[u].l+tr[u].r>>1;
    pushdown(u);
    ll res=0;
    if(l<=mid)
    res=query(u<<1,l,r);
    if(r>mid)
    res+=query(u<<1|1,l,r);
    return res;
}
int getmax(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r)
    return tr[u].ma;
    int mid=tr[u].l+tr[u].r>>1;
    pushdown(u);
    int res=-inf;
    if(l<=mid)
    res=getmax(u<<1,l,r);
    if(r>mid)
    res=max(res,getmax(u<<1|1,l,r));
    return res;
}
int getmin(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r)
    return tr[u].mi;
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    int res=inf;
    if(l<=mid)
    res=getmin(u<<1,l,r);
    if(r>mid)
    res=min(res,getmin(u<<1|1,l,r));
    return res;
}
int main(){
    int n;
    cin>>n;
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int m;
    build(1,1,n);
    cin>>m;
    while(m--){
        int opt,l,r;
        int x;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1){
            scanf("%d",&x);
            add(1,l,r,x);
        }
        else if(opt==2){
            scanf("%d",&x);
            modify(1,l,r,x);
        }
        else if(opt==3){
            scanf("%d",&x);
            change(1,l,r,x);
        }
        else if(opt==4){
            printf("%lld\n",query(1,l,r));
        }
        else if(opt==5){
            printf("%d\n",getmax(1,l,r));
        }
        else
            printf("%d\n",getmin(1,l,r));
    } 
}
