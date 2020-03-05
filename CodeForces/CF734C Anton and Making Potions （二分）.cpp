分析：
这道题很明显需要是暴力枚举第一维并且二分第二维，因为第二维是单调的
有几个坑点，首先可以都不用，其次可以只用一个，另外，我在做这题犯了一个巨大的错误，就是我光顾着判断二分情况的花费有没有超，却忘记了第一步的花费也可能超过要求
因此这里要注意一下
=============================
代码：
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<queue>
#include<map>
#include<cstring>
#include<string>
using namespace std;
typedef long  long ll;
const int N=2e5+10;
struct node{
    ll a;
    ll b;
}s[N];
struct qi{
    ll d;
    ll c;
}q[N];
int main(){
    int i;
    ll n,m,k;
    cin>>n>>m>>k;
    ll x,h;
    cin>>x>>h;
    ll res=(ll)x*n;
    for(i=1;i<=m;i++){
        scanf("%lld",&s[i].a);
    }
    for(i=1;i<=m;i++){
        scanf("%lld",&s[i].b);
    }
    for(i=1;i<=k;i++){
        scanf("%lld",&q[i].c);
    }
    for(i=1;i<=k;i++){
        scanf("%lld",&q[i].d);
    }
    ll tmp;
    ll ans=res;
    s[0].a=x;
    s[0].b=0;
    for(i=0;i<=m;i++){
        int cost=s[i].b;
        if(cost>h)
            continue;
        int l=0,r=k;
        while(l<r){
            ll mid=l+r+1>>1;
            if(cost+q[mid].d<=h){
                l=mid;
            }
            else
                r=mid-1;
        }
        tmp=(n-q[l].c)*s[i].a;
        ans=min(ans,tmp);
    }
    cout<<ans<<endl;
    return 0;
}
