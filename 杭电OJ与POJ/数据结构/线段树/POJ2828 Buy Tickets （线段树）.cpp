分析：
这道题我们发现如果从前面往后插，我们并不能得到正确答案，因为位置一直在变化，
所以我们考虑从后往前插，最后一个数的位置肯定是正确的，接下来的树根据这个数的位置而改变
这里用到了一个权值线段树的一些想法，根据节点的大小来选择插哪边
======================================================
代码；
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map> 
#include<vector> 
using namespace std;
typedef  long long ll;
const int N=5e5+10;
const int inf=0x3f3f3f3f;
struct qi{
    int x;
    int num;
}q[N];
struct node{
    int l,r;
    int size;
    int num;
}tr[N<<2];
int ans[N];
void pushup(int u){
    tr[u].size=tr[u<<1].size+tr[u<<1|1].size;
}
void build(int u,int l,int r){
    if(l==r){
        tr[u]={l,r,1};
    }
    else{
        tr[u]={l,r};
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
void modify(int u,int pos,int x){
    if(tr[u].l==tr[u].r){
        ans[tr[u].l]=x;
        tr[u].size--;
        return ;
    }
    if(pos<=tr[u<<1].size)
    modify(u<<1,pos,x);
    else
    modify(u<<1|1,pos-tr[u<<1].size,x);
    pushup(u);
}
int main(){
    int n;
    while(cin>>n){
        int i;
        build(1,1,n);
        memset(ans,0,sizeof ans);
        for(i=1;i<=n;i++){
            scanf("%d%d",&q[i].x,&q[i].num);        
        }
        for(i=n;i>=1;i--){
            modify(1,q[i].x+1,q[i].num);
        }
         for(i=1;i<=n;i++)
         printf("%d ",ans[i]);
         cout<<endl;
    }
}
