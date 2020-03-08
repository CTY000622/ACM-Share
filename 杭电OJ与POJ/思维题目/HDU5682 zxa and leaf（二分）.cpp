分析：
这道题很容易看出是求最大值的最小值，然后我们发现每个边的取值范围都是一段区间，这就是常见的用区间表示是否满足题意，当左边界大于右边界的时候就不满足
=========================================
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
const int N=1e5+10;
const int inf=0x3f3f3f3f;
int n,k;
vector<int> g[N];
struct node{
    int l,r;
    int t1,t2;
}tr[N];
void init(){
    int i;
    for(i=0;i<=n;i++){
        tr[i].l=1;
        tr[i].r=inf;
        g[i].clear();
    }
}
bool dfs(int u,int fa,int x){
    tr[u].t1=tr[u].l;
    tr[u].t2=tr[u].r;
    int i;
    for(i=0;i<g[u].size();i++){
        int j=g[u][i];
        if(j==fa)
            continue;
        if(!dfs(j,u,x))
            return false;
        tr[u].t1=max(tr[u].t1,max(1,tr[j].t1-x));
        tr[u].t2=min(tr[u].t2,min(inf,tr[j].t2+x));
        if(tr[u].t1>tr[u].t2)
            return false;
    }
    return true;
}
bool check(int mid){
    return dfs(1,-1,mid);
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        init();
        int i;
        for(i=0;i<n-1;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for(i=0;i<k;i++){
            int u,w;
            scanf("%d%d",&u,&w);
            tr[u].l=tr[u].r=w;
        }
        int l=0,r=inf;
        while(l<r){
            int mid=l+r>>1;
            if(check(mid))
                r=mid;
            else
                l=mid+1;
        }
        cout<<l<<endl;
    }
}#include<iostream>
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
int n,k;
vector<int> g[N];
struct node{
    int l,r;
    int t1,t2;
}tr[N];
void init(){
    int i;
    for(i=0;i<=n;i++){
        tr[i].l=1;
        tr[i].r=inf;
        g[i].clear();
    }
}
bool dfs(int u,int fa,int x){
    tr[u].t1=tr[u].l;
    tr[u].t2=tr[u].r;
    int i;
    for(i=0;i<g[u].size();i++){
        int j=g[u][i];
        if(j==fa)
            continue;
        if(!dfs(j,u,x))
            return false;
        tr[u].t1=max(tr[u].t1,max(1,tr[j].t1-x));
        tr[u].t2=min(tr[u].t2,min(inf,tr[j].t2+x));
        if(tr[u].t1>tr[u].t2)
            return false;
    }
    return true;
}
bool check(int mid){
    return dfs(1,-1,mid);
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        init();
        int i;
        for(i=0;i<n-1;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for(i=0;i<k;i++){
            int u,w;
            scanf("%d%d",&u,&w);
            tr[u].l=tr[u].r=w;
        }
        int l=0,r=inf;
        while(l<r){
            int mid=l+r>>1;
            if(check(mid))
                r=mid;
            else
                l=mid+1;
        }
        cout<<l<<endl;
    }
}
