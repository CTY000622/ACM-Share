分析：
网上很多人说这是一道线段树水题，但是我却错了一晚上，下面我来分析一下这道题做的时候会遇到的困惑
如果看到了这篇题解，我相信你已经看到其他题解中离散化的正确方法，这也是本题中最难的一个地方
但是我发现网上的题解并没有详细讲述为什么这样就能防止错误情况，对于初学者来说或许难以理解原理
1.首先为什么只有在两个相邻大于1的数之间插入一个值就能防止因为离散放缩后导致的区间覆盖问题？
我们拿1 10      1 4    6 10这个常例来说
因为我们在离散化的时候只关心相对大小，所以这个6就是4之后的一个数，但是我们显然知道这样覆盖了5这个区间
我们在相邻大于1的数之间插入一个数，不管这个数是多大，只要他比前面的数大比后面的数小。我们都能够在离散化后的区间中模拟出来真实区间的间隔，并且我们不关心这个间隙有多大
只需要存在间隙，我们就能模拟成真实的情况，因为离散后的区间一定会被间隔开，所以这个数可以是任何数，例如两个数的平均值，或者是大数-1
而相邻差1的数，他在真实的区间中本来也就是相邻的，所以无需这种操作
2.为什么我们要对每个满足情况的数都进行这样的操作？就是为什么从头遍历？
其实我们只需要在真实的询问之中插入数即可 比如在1 4 6 10之间插数，但是我们已经离散化了，并不知道哪个区间是我们真的要操作的询问，并且我们发现，在不是题目中询问的插数并不影响真实的答案
为了方便，我们都插一插，这样肯定覆盖了真实要插的区间。
3.为什么我总是runtime error？一个是很有可能你在询问中判定左右节点相等的时候退出，一个是线段树开小了，一个是你写了一个int函数，但是在该返回值的时候忘记return了
如果上面三个都不是，那就是你程序写的有问题
4.网上大部分都是数组来存，我习惯用结构体存储咋办？
那太好了，我这篇题解就是用了结构体存储，下面我们边看代码边理解其中的精妙之处
=============================================================
代码：
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector> 
using namespace std;
const int N=1e5+10;
int ans[N];
int li[N],ri[N];  //存储询问 
vector<int> num;
struct node{
    int l,r;
    int lazy;
}tr[N<<2];
int n;
void build(int u,int l,int r){
    if(l==r){
        tr[u]={l,r,0};
        return ;
    } 
    else{
        tr[u]={l,r,0};
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
    }
}
void pushdown(int u){  //当我们的懒标记不是0，说明该段染色，所以往下传递 
    if(tr[u].lazy!=0){
        tr[u<<1].lazy=tr[u<<1|1].lazy=tr[u].lazy;
        tr[u].lazy=0;
    }
}
void modify(int u,int l,int r,int x){
    if(tr[u].l>=l&&tr[u].r<=r){
        tr[u].lazy=x;
        return ;
    }
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid)
    modify(u<<1,l,r,x);
    if(r>mid)
    modify(u<<1|1,l,r,x);   //按道理我们这有个pushup操作，但是本题并不需要根据儿子节点来更新父亲节点也能做 
}
void query(int u,int l,int r){ //这个询问和普通线段树的询问略有不同 
    if(tr[u].lazy){   // 如果懒标记存在，说明这个区间是单色的 
        ans[tr[u].lazy]=1;  //将有被染色的颜色记录下来 
        return ;
    }
    if(tr[u].l==tr[u].r)  //一定要这个判断条件，否则你没有递归终止条件，就rt了 
    return ;              //这与普通线段树的格式有区别，但是原理相同 
    int mid=tr[u].l+tr[u].r>>1;
    pushdown(u);  
    query(u<<1,l,r);//如果是0，有两种情况，一个是没有染色，一个是有多种颜色 
    query(u<<1|1,l,r);
}
void Solve(){    //离散化操作和插点操作 
    int i,x,y;
    sort(num.begin(),num.end());
    num.erase(unique(num.begin(),num.end()),num.end());
    int m=num.size();
    for(i=0;i<m-1;++i)
        if(num[i+1]-num[i]>1)
            num.push_back((num[i+1]-1));
    sort(num.begin(),num.end());        
    build(1,0,num.size()-1);
    for(i=1;i<=n;++i)
    {    x=lower_bound(num.begin(),num.end(),li[i])-num.begin();
        y=lower_bound(num.begin(),num.end(),ri[i])-num.begin();
        modify(1,x,y,i);
    }
    int res=0;
    memset(ans,0,sizeof(ans));
    query(1,0,num.size()-1);
    for(i=1;i<=n;++i)
        if(ans[i])
            res++;
    printf("%d\n",res);
}
int main(){    
    int t,i;
    scanf("%d",&t);
    while(t--){    
        scanf("%d",&n);
        num.clear();
        for(i=1;i<=n;++i){    
            scanf("%d %d",&li[i],&ri[i]);
            num.push_back(li[i]);
            num.push_back(ri[i]);
        }
        Solve();
    }
    return 0;
}
