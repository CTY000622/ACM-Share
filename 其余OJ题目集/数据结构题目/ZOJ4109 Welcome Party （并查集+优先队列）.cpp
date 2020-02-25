分析：
首先提取题目信息，我们需要计算朋友的关系，以及计算不开心值。
其实看题目我们很容易就有并查集的感觉，之后我们要去验证这个算法是正确的
题目要求的是求不开心值，那么我们就可以想到使用并查集求集合总数就可以了
虽然朋友不存在传递性，但是这并不影响不开心值的大小，因为如果a和b是朋友，b和c是朋友
那么虽然a和c不一定是朋友，但是假如a进去了，那么我们可以走b再走c，这样不会增加不开心值。
因为我们有媒介，也就是并查集的传递性没有破坏。
但是题目有个要求是说字典序最小，其实这也是常见的做法，我怀疑很有可能是出题人不想写spj所以才出了这个要求，这只需要使用优先队列就可以弹出符合条件的最小值了
显然根据经验，我们可以用向前星或者是vector存储，这里写vector比较简单，毕竟不是正宗的图论题目
我们发现，有几棵森林，就有多少个不开心值，所以不开心值就求出来了
接下来我们需要设计一个0点，来存每个集合的头结点，这样比较方便，不然不好遍历所有的集合
之后只需要常规操作，弹最小值遍历即可，每次遍历一个vector，把没出现过的存进来。
=============================================================================
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
const int N=1e6+10;
int p[N];
int st[N];
int pos[N];
int idx;
vector<int> v[N];
int find(int x){
    if(p[x]!=x)
    p[x]=find(p[x]);
    return p[x];
}
void bfs(int u){
    priority_queue<int,vector<int>,greater<int>> q;
    q.push(0);
    while(q.size()){
        int t=q.top();
        q.pop();
        if(!st[t]){
            st[t]=1;
            pos[idx++]=t;
            for(int i=0;i<v[t].size();i++){
                if(!st[v[t][i]]){
                    q.push(v[t][i]);
                }
            }
        }
    }
}
int main(){
    int t;
    int n,m;
    cin>>t;
    while(t--){
        cin>>n>>m;
        int i;
        idx=0;
        for(i=0;i<=n;i++){
            p[i]=i;
            v[i].clear();
            st[i]=0;
        }
        for(i=1;i<=m;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            int pa=find(a),pb=find(b);
            if(pa>pb){
                p[pa]=pb;
            }
            else{
                p[pb]=pa;
            }
            v[a].push_back(b);
            v[b].push_back(a);
        }
        int ans=0;
        for(i=1;i<=n;i++){
            if(p[i]==i){
                v[0].push_back(i);
                ans++;
            }
        }
        bfs(0);
        printf("%d\n",ans);
        for(i=1;i<idx-1;i++){
            printf("%d ",pos[i]);
        }    
        printf("%d\n",pos[i]);
    }
}
