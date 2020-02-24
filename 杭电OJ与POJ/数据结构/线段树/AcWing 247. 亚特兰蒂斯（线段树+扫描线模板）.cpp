分析：
在这篇题解中我不打算介绍线段树扫描线原理，因为网上有更多的人介绍的更好，我打算和大家分享一些扫描线操作的细节问题。
1.首先本题是特殊的线段树操作，因为根据我们对题目的了解，可以不用写pushdown操作(仅对矩形有效)，原因如下：
在线段树中，有两个地方需要pushdown操作，第一个是修改时，第二个是查询时
首先我们因为我们查询的时候，总是查询最大的区间，所以查询的时候不会分裂传递懒标记
其次，在修改操作时，我们只有两个操作，一个是加一个是减，在减操作时我们减的都是之前已经加过的区间，所以不需要分裂传递
而在加的时候，我们并不需要在意一个区间到底加上了多少，只需要在意是否是大于0，所以也不用传递懒标记
2.线段树本质是维护区间，也就是说我们离散化后存点是没有意义的，比如说y1,y2表示的是y1-y2,y2-y3这两个区间，所以有n个点，只有n-1个区间，我们修改时要对右端点-1，否则我们会出现如下情况
我们必定会分裂之后分别修改l-mid,mid+1-r，然后这就会忽略mid-mid+1这之间的内容，所以是错误的。
3.pushup操作中的三个条件分别代表着，加入cnt存在，说明这段区间都要计算上去，假如cnt不存在，但是左端点不等于右端点，说明这段区间中并不是所有的地方都覆盖，因此要从已经更新过的子节点更新这段区间
如果左端点等于右端点，说明这段区间已经被消除掉了，那么这段区间的长度就要归0
================================================
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int a[N];
int n,m;
vector<double> ys;
struct s{
    double x;
    double y1;
    double y2;
    int k; 
    bool operator <(const  s &t) const{
      return x<t.x;
    }
}sg[N*2];
struct node{
    int l,r;
    int cnt;
    double len;
}tr[N*8];
int find(double x){
    int pos=lower_bound(ys.begin(),ys.end(),x)-ys.begin();
    return pos;
}
void pushup(int u){
    if(tr[u].cnt){
        tr[u].len=ys[tr[u].r+1]-ys[tr[u].l];
    }
    else if(tr[u].l!=tr[u].r)
    tr[u].len=tr[u<<1].len+tr[u<<1|1].len;
    else
    tr[u].len=0; 
    
}
void build(int u,int l,int r){
    tr[u]={l,r,0,0};
    if(l!=r){
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
    }
}
void modify(int u,int l,int r,int k){
    if(tr[u].l>=l&&tr[u].r<=r){
        tr[u].cnt+=k;
        pushup(u);
    }
    else{
        int mid=tr[u].l+tr[u].r>>1;
        if(l<=mid)
        modify(u<<1,l,r,k);
        if(r>mid)
        modify(u<<1|1,l,r,k);
        pushup(u);
    }
}
int main(){
    int T=1;
    int n;
    while(cin>>n,n){
    ys.clear();
    int i;
    double x1,x2,y1,y2;
    int cnt=1;
    for(i=1;i<=n;i++){
               cin>>x1>>y1>>x2>>y2;
               sg[cnt++]={x1,y1,y2,1};
               sg[cnt++]={x2,y1,y2,-1};
            ys.push_back(y1);
            ys.push_back(y2); 
    }
    sort(sg+1,sg+1+2*n);
    sort(ys.begin(),ys.end());
    ys.erase(unique(ys.begin(),ys.end()),ys.end());
    build(1,0,ys.size()-2);
    double sum=0;
    for(i=1;i<=2*n;i++){
        if(i>1){
            sum+=tr[1].len*(sg[i].x-sg[i-1].x);
           
        } 
        modify(1,find(sg[i].y1),find(sg[i].y2)-1,sg[i].k);
    }
    printf("Test case #%d\n",T++);
    printf("Total explored area: %.2f\n\n",sum);
    }
}
