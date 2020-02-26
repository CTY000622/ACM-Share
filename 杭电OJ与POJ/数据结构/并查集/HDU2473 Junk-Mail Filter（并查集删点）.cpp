分析：
本题是并查集删点的经典例题，并查集删点操作的核心就是虚点，利用res数组映射新点，这样就不会对原来的内容造成干扰。
例如 1，2，3，4 ，这些点再普通操作下变成一个集合，根节点是4。
那么如果我们要删除4，我们考虑将4映射到5上，值得一提的是，不是直接把p[4]=5
而是我们在刚开始就设置一个res数组，表示res[4]=5,之后，p[5]=5，这样做的目的是，
不对当前点进行修改，而是更改了当前点的映射，再对映射后的点进行修改。如此操作我们就会发现
123的根节点依旧是4，而4映射到5这个点上，根节点是5，这样就分离成两个集合了，而我们在这之后永远不会对4本身进行操作，如果想操作4，都会操作到5上
这也就是为什么删除这个点不会影响原先绑定在它上面的其他点。
那么我们在计算集合数量的时候，也不能像以前一样计算，而是利用哈希数组计算是否重复出现
因为 假如123的根节点是4，我们分离4后，又合并4，这时候，5又可能连回到4上，但是我们都是通过res数组进行计算（因为他代表了真实的信息），因此就会产生没有根节点是本身的情况。
=================================================================
代码：
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<string> 
#include<set>
#include<map>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1e5+1e6+10;
int p[N];
int res[N];
int idx;
int find(int x){
    if(p[x]!=x){
        p[x]=find(p[x]);
    }
    return p[x];
}
void change(int x){
    res[x]=idx;
    p[idx]=idx;
    idx++;
}
int h[N];
int main(){
   int i;
   int t=1;
   int n,m;
   while(cin>>n>>m){
        if(n==0&&m==0)
        break;
        for(i=0;i<n;i++){
        res[i]=i; 
           p[i]=i;
           idx=n;
    } 
        for(i=1;i<=m;i++){
            string s;
            cin>>s;
            if(s=="M"){
                int a,b;
            cin>>a>>b;
            int pa=find(res[a]),pb=find(res[b]);
            if(pa!=pb){
            p[pa]=pb;
            }        
        }
        else{
            int a;
            cin>>a;
            change(a);
        }
    }
    int ans=0;
    memset(h,0,sizeof h);
    for(i=0;i<n;i++){
        int x=find(res[i]);
        if(!h[x])
        h[x]=1,ans++;
    }
    printf("Case #%d: %d\n", t++, ans);
   }
   
}
