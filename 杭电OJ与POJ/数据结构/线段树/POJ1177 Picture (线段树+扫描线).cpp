分析：
本题求周长，其实思路与面积完全相似
离散化+扫描线，本题甚至可以不用离散化，因为数据范围并不是特别大
我们能想到的暴力就是先算一遍横的，再算一遍竖的，我不知道这样能不能过，或许可以
但是我们发现其实可以在求竖线的时候顺便把横线求了，因为一条横线的长度永远是相邻x的差值
我们只需要考虑两个相邻的x有几条线，这个时候，我们可以在线段树中维护一个num表示有几条不连续的竖线，通过这样就可以算出横线的个数为2*num
但是我们还要维护一个ls和一个rs，表示我这个区间的左端和右端有没有覆盖，考虑这个是因为在更新父节点的时候会产生冲突，我们举个例子
左儿子是1-3,右儿子是4-6,我们假设每个儿子里面都有一条不连续的线，也就是说1-3和4-6都被覆盖了。
那么在连续的时候，如果左儿子的rs和右儿子的ls都是1，那么其实这是一条连续的区间，而不是1+1=2；
================================================================
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
struct node{
    int l,r;
    int cnt;
    int len;
    int num;
    int ls;
    int rs;
}tr[N];
struct qi{
    int x;
    int y1;
    int y2;
    int k;
    bool operator <(const qi&t){
        return x<t.x; 
    }    
}q[N];
vector<int> num;
int find(int x){
    return lower_bound(num.begin(),num.end(),x)-num.begin()+1;
}
void build(int u,int l,int r){
    if(l==r){
        tr[u].l=tr[u].r=l;
    }
    else{
        tr[u].l=l;
        tr[u].r=r;
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
    } 
}
void pushup(int u){
    if(tr[u].cnt){
        tr[u].len=num[tr[u].r]-num[tr[u].l-1];
        tr[u].ls=tr[u].rs=1;
        tr[u].num=1;
    }
    else if(tr[u].l==tr[u].r){
        tr[u].len=0;
        tr[u].num=0;
        tr[u].ls=tr[u].rs=0;
    }
    else{
        tr[u].len=tr[u<<1].len+tr[u<<1|1].len;
        tr[u].num=tr[u<<1].num+tr[u<<1|1].num;
        tr[u].ls=tr[u<<1].ls,tr[u].rs=tr[u<<1|1].rs;
        if(tr[u<<1].rs==1&&tr[u<<1|1].ls==1)
        tr[u].num-=1; 
    }
}
void modify(int u,int l,int r,int x){
    if(tr[u].l>=l&&tr[u].r<=r){
        tr[u].cnt+=x;
        pushup(u);
        return ;
    }
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid)
    modify(u<<1,l,r,x);
    if(r>mid)
    modify(u<<1|1,l,r,x);
    pushup(u);
}
int main(){
    int n;
    cin>>n;
    int i;
    int idx=1;
    for(i=1;i<=n;i++){
        int x1,x2,y1,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        q[idx].x=x1,q[idx].y1=y1,q[idx].y2=y2,q[idx].k=1;
        idx++;
        q[idx].x=x2,q[idx].y1=y1,q[idx].y2=y2,q[idx].k=-1;
        idx++;
        num.push_back(y1);
        num.push_back(y2);
    }
    sort(q+1,q+1+idx);
    sort(num.begin(),num.end());
    num.erase(unique(num.begin(),num.end()),num.end());
    int tmp=0;
    int res=0;
    build(1,1,num.size()-1);
    for(i=1;i<=idx;i++){
        tmp=tr[1].len;
        if(i>=2){
            res+=2*tr[1].num*(q[i].x-q[i-1].x);
        }
        modify(1,find(q[i].y1),find(q[i].y2)-1,q[i].k);
        res+=abs(tr[1].len-tmp);
    }
    cout<<res<<endl;
}
