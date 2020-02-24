分析：
这题用容斥定理做会代码简单不少，但是一个是我数学不好，另一个我感觉这就是个扫描线模板题
首先也是求面积并，但是本题不是所有的矩形都用得到，我们根据题目的询问来用vis存储用得到的矩形
注意，因为我们已经离散化了，所以当前的矩形不是原先的矩形排序，而询问的时候是告诉我们原先矩形的位置，所以我们在输入的时候记录一下他的pos
本题很卡时限，做到以下几点就没问题了
1.用c++交
2.最大的N不要设的太大，本题只有20个矩形，以前我们碰到往往是1e5级别的，所以像我第一次就直接开了1e5，我没想到就这点建树的时间就超时了，所以要开30就行
3.没有必要重复建树，因为这是扫描线，所有矩形都有出边和入边，全部遍历完后，线段树中一定是空的
4.以上poj就能成功通过，记得用scanf，如果你的做法poj是tle的，去杭电同题交一下，poj的数据被加强过，如果杭电还是tle，并且卡不了常了，应该是做法问题。
==================================================================================
代码：
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=30;
int a[N];
int n,m;
vector<double> ys;
struct s{
    int x;
    int y1;
    int  y2;
    int k; 
    int num;
    bool operator <(const  s &t) const{
      return x<t.x;
    }
}sg[N*2];
struct node{
    int l,r;
    int cnt;
    int  len;
}tr[N*8];
int find(int  x){
    int pos=lower_bound(ys.begin(),ys.end(),x)-ys.begin()+1;
    return pos;
}
void pushup(int u){
    if(tr[u].cnt){
        tr[u].len=ys[tr[u].r]-ys[tr[u].l-1];
    }
    else if(tr[u].l!=tr[u].r)
    tr[u].len=tr[u<<1].len+tr[u<<1|1].len;
    else
    tr[u].len=0; 
    
}
void build(int u,int l,int r){
    tr[u].l=l;
    tr[u].r=r;
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
int vis[N];
int main(){
    int T=1;
    int n;
    while(cin>>n>>m){
        if(n==0&&m==0)
        break;
    ys.clear();
    int i;
    int  x1,x2,y1,y2;
    int cnt=1;
    for(i=1;i<=n;i++){
            cin>>x1>>y1>>x2>>y2;
            sg[cnt].x=x1,sg[cnt].y1=y1,sg[cnt].y2=y2,sg[cnt].k=1,sg[cnt].num=i;
            cnt++;
            sg[cnt].x=x2,sg[cnt].y1=y1,sg[cnt].y2=y2,sg[cnt].k=-1,sg[cnt].num=i;
            cnt++;
            ys.push_back(y1);
            ys.push_back(y2); 
    }
    sort(sg+1,sg+1+2*n);
    sort(ys.begin(),ys.end());
    ys.erase(unique(ys.begin(),ys.end()),ys.end());
    build(1,1,ys.size()-1);
    int sign=1;printf("Case %d:\n",T++);
    for(i=1;i<=m;i++){
        int r;
        memset(vis,0,sizeof vis);
        scanf("%d",&r);
        int j;
        for(j=1;j<=r;j++){
            int x;
            scanf("%d",&x);
            vis[x]=1; 
        }
        int res=0;
        int pre=0;
        for(j=1;j<=2*n;j++){
            if(!vis[sg[j].num])
            continue;
            if(pre){
                res+=tr[1].len*(sg[j].x-sg[pre].x);
            }
            modify(1,find(sg[j].y1),find(sg[j].y2)-1,sg[j].k);
            pre=j;
        }
    
    printf("Query %d: %d\n",sign++,res);
    }
    printf("\n");
    }
}
