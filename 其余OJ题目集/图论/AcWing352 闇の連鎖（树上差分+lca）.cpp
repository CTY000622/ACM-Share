分析：
这道题的我们知道如果在两个点之间有附加边，其实就相当于在这个回路上的每条边都权值+1，这样就可以通过差分数组来快速求取大小
这里的精髓就是在输入的两个位置+1，而在他们的lca上-=2；
================================
代码：
#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1e6+10;
const int inf=0x3f3f3f3f;
int e[N],ne[N],h[N],idx;
int fa[N][16];
int depth[N];
int d[N];
int m;
void add(int a,int b){
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void bfs(){
    memset(depth,0x3f,sizeof depth);
    depth[0]=0,depth[1]=1;
    queue<int> q;
    q.push(1);
    while(q.size()){
        int t=q.front();
        q.pop();
        int i;
        for(i=h[t];i!=-1;i=ne[i]){
            int j=e[i];
            if(depth[j]>depth[t]+1){
                depth[j]=depth[t]+1;
                q.push(j);
                fa[j][0]=t;
                for(int k=1;k<=15;k++){
                    fa[j][k]=fa[fa[j][k-1]][k-1];
                }
            }
        }
    }
}
int lca(int a,int b){
    if(depth[a]<depth[b])
        swap(a,b);
    int i;
    for(i=15;i>=0;i--){
        if(depth[fa[a][i]]>depth[b])
            a=fa[a][i];
    }
    if(a==b)
        return a;
    for(i=15;i>=0;i--){
        if(fa[a][i]!=fa[b][i]){
            a=fa[a][i];
            b=fa[b][i];
        }
    }
    return fa[a][0];
}
int ans=0;
int dfs(int u,int p){
    int res=d[u];
    int i;
    for(i=h[u];i!=-1;i=ne[i]){
        int s=0;
        int j=e[i];
        if(j==p)
            continue;
        s+=dfs(j,u);
        if(s==0)
            ans+=m;
        else if(s==1)
            ans++;
        res+=s;
    }
    return res;
}
int main(){
    int n;
    cin>>n>>m;
    int i;
    memset(h,-1,sizeof h);
    for(i=1;i<n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    bfs();
    for(i=1;i<=m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        int p=lca(a,b);
        d[a]++,d[b]++,d[p]-=2;
    }
    dfs(1,-1);
    printf("%d\n",ans);
}
