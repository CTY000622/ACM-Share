分析：
与这道题相似的还有poj一道贴海报的题目，但这道题更加经典
典型的线段树合并求区间子段和模型，但是不同的是加了一个离散化，这也是最难的地方
本题思路：
1.设计lmax，rmax tmax来表示左边最长连续，总共最长连续和右边最长连续
2.设计懒标记为-1，0，1表示这区间是否都是黑或白或混合，如果不设懒标记，线段树的复杂度无法保证。
3.以上这中模型的通解，那么下面就是离散化部分
对于区间染色和区间合并问题，不能简单离散化，因为我们知道，这样会导致中间的部分值缺失，所以我们需要将每个位置的左右点都加进去保证不会覆盖。
4.查询的时候一定要注意要找最小的，也就是越左越好
5.我是用vector离散化，在求sum的时候一定要考虑好到底是什么减什么。
=====================================
#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<string>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1e5+10;
const int inf=0x3f3f3f3f;
struct node{
    int l,r;
    int lmax;
    int rmax;
    int tmax;
    int lazy;
}tr[N<<2];
struct qi{
    int a;
    int b;
    string s;
}q[2100];
vector<int> num;
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
        tr[u]=(node){l,l,0,0,0,1};
    }
    else{
        tr[u]=(node){l,r,0,0,0,1};
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
    }
}
void pushdown(int u){
    tr[u<<1].lazy=tr[u<<1|1].lazy=tr[u].lazy;
    if(tr[u].lazy==1){
        tr[u<<1].lmax=tr[u<<1].rmax=tr[u<<1].tmax=0;
        tr[u<<1|1].lmax=tr[u<<1|1].rmax=tr[u<<1|1].tmax=0;
    }
    else{
        tr[u<<1].lmax=tr[u<<1].rmax=tr[u<<1].tmax=num[tr[u<<1].r-1]-num[tr[u<<1].l-2];
        tr[u<<1|1].lmax=tr[u<<1|1].rmax=tr[u<<1|1].tmax=num[tr[u<<1|1].r-1]-num[tr[u<<1|1].l-2];
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
            tr[u].lmax=tr[u].rmax=tr[u].tmax=num[tr[u].r-1]-num[tr[u].l-2];
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
int find(int x){
    return lower_bound(num.begin(),num.end(),x)-num.begin()+1;
}
int query(int u,int x){
    if(tr[u<<1].lmax==x){
        return num[tr[u].l-1];
    }
    if(tr[u].lazy)
        pushdown(u);
    if(tr[u<<1].tmax==x)
        return query(u<<1,x);
    if(tr[u<<1].rmax+tr[u<<1|1].lmax==x)
        return num[tr[u<<1].r-1]-tr[u<<1].rmax+1;
    else
        return query(u<<1|1,x);
}
int main(){
    int n;
    while(cin>>n){
        int i;
        if(n==0){
            cout<<"Oh,my god"<<endl;
            continue;
        }
        num.clear();
        for(i=1;i<=n;i++){
            cin>>q[i].a>>q[i].b>>q[i].s;
            if(q[i].a>q[i].b)
                swap(q[i].a,q[i].b);
            num.push_back(q[i].a);
            num.push_back(q[i].b);
            num.push_back(q[i].a-1);
            num.push_back(q[i].a+1);
            num.push_back(q[i].b-1);
            num.push_back(q[i].b+1);
        }
        sort(num.begin(),num.end());
        num.erase(unique(num.begin(),num.end()),num.end());
        build(1,1,(int)num.size());
        for(i=1;i<=n;i++){
            int l=find(q[i].a);
            int r=find(q[i].b);
            if(q[i].s=="w"){
                modify(1,l,r,-1);
            }
            else{
                modify(1,l,r,1);
            }
        }

        int x=tr[1].tmax;
        if(x==0){
            cout<<"Oh,my god"<<endl;
        }
        else{
            int y1=query(1,x);
            int y2=y1+tr[1].tmax-1;
            cout<<y1<<" "<<y2<<endl;
        }
    }
}
