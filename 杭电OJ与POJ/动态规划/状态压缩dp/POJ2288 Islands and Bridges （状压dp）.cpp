分析：
本题就是经典的哈密顿回路，但是有一个附加条件，就是如果有三个相邻，那么可以附加值
这样我们就可以枚举4维，判断条件后再加上
本题有几个坑点
1.爆int
2.有可能不存在这样的路
3.题目定义的路是不重复的，所以要/2
4.本题应该先预处理两个的情况，再用他推大的情况，我们普通的是用小的来维护现在，而这道题用现在来维护以后
其实可以不用预处理，在循环内判断，但是预处理比较简单
5.我们设计的状态为f[i][j][k]，当前集合为i，在j，由k跳过来
6.特判一个点的情况
============================
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
typedef pair<int,int> pll;
const int N=14;
const int inf=0x3f3f3f3f;
ll f[1<<N][N][N];
ll num[1<<N][N][N];
int n,m;
int g[N][N];
int w[N]; 
int main(){
    int i,j,k;
    int q;
    cin>>q;
    while(q--){
        memset(num,0,sizeof num);
        memset(g,0,sizeof g);
        cin>>n>>m;
    for(i=0;i<n;i++)
    cin>>w[i];
    for(i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        g[u-1][v-1]=1;
        g[v-1][u-1]=1;
    }
    if(n==1){
        cout<<w[0]<<" 1"<<endl;
        continue;
    }
    memset(f,-1,sizeof f);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(g[i][j]){
                f[1<<i|1<<j][i][j]=w[i]+w[j]+w[i]*w[j];
                num[1<<i|1<<j][i][j]=1;
            }
        }
    }
    int l;
    for(i=3;i<1<<n;i++){
        for(j=0;j<n;j++){
            if(!(i>>j&1))
            continue;
            for(k=0;k<n;k++){
                if(k==j||!(i>>k&1))
                continue;
                if(f[i][j][k]==-1) 
                continue;
                for(l=0;l<n;l++){
                    if(i>>l&1||!g[j][l])
                    continue;
                    int r=i|(1<<l);
                    ll tmp=f[i][j][k]+w[j]*w[l]+w[l];
                    if(g[k][l])
                    tmp+=w[k]*w[j]*w[l];
                    if(f[r][l][j]<tmp){
                        f[r][l][j]=tmp;
                        num[r][l][j]=num[i][j][k];
                    }            
                    else if(f[r][l][j]==tmp){
                        num[r][l][j]+=num[i][j][k];
                    }
                }                
            }
        } 
    }
    ll ans=0;
    ll res=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(f[(1<<n)-1][i][j]>ans){
                ans=f[(1<<n)-1][i][j];
                res=num[(1<<n)-1][i][j];
            }
            else if(f[(1<<n)-1][i][j]==ans){
                res+=num[(1<<n)-1][i][j];
            }
        }
    }
    if(!ans)
    cout<<"0 0"<<endl;
    else
    cout<<ans<<" "<<res/2<<endl;
    }
    return 0;
}
