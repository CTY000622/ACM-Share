分析：
本题从题目给出的条件我们发现了最小生成树的影子，也就是kruscal的影子
其实我们在写kruscal的时候就是利用并查集的思想来写的
这题需要注意的是，我们在求取的过程中l并不需要减少，我们只要最小生成树中的最大边权小于等于l就行了
这就让我们想到了可以从小到大对边权排序，之后枚举维护树集合，如果两个点还不在同一颗树中那就合并
那么答案就是求取的路径的个数，我们知道每个边对路径的个数的贡献就是左边节点✖右边节点，根据乘法原理可得。
本题还需要注意的是，询问的个数很多，如果在线查询，每次从头开始，会超时，因此用离线思想，将l也排序，这样就只需O(N)就能做了
========================================
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
const int N=1e5+10;
int n,m;
int p[N];
int size[N];
struct node{
    int a,b;
    int w;
    bool operator <(const node &t){
        return w<t.w;
    }
}s[N];
struct qi{
    int l;
    int k;
    bool operator <(const qi&t){
        return l<t.l;
    }
}q[N];
int ans[N];
int find(int x){
    if(p[x]!=x){
        p[x]=find(p[x]);
    }
    return p[x];
}
int main(){
    int t;
    while(cin>>n>>m>>t){
        int i;
        for(i=1;i<=n;i++){
            p[i]=i;
            size[i]=1;
        }
        for(i=1;i<=m;i++){
            int u,v;
            int w;
            scanf("%d%d%d",&u,&v,&w);
            s[i].a=u,s[i].b=v,s[i].w=w;
        }
        sort(s+1,s+1+m);
        for(i=1;i<=t;i++){
            scanf("%d",&q[i].l);
            q[i].k=i;
        }
        sort(q+1,q+1+t);
        int pos=1;
        int res=0;
        for(i=1;i<=t;i++){
            while(pos<=m&&s[pos].w<=q[i].l){
                 int pa=find(s[pos].a),pb=find(s[pos].b);
                 if(pa!=pb){
                     res+=size[pa]*size[pb];
                     p[pa]=pb;
                     size[pb]+=size[pa];
                 }
                 pos++;
            }
            ans[q[i].k]=res;
        }
        for(i=1;i<=t;i++)
        printf("%d\n",ans[i]);
    
    }
}
