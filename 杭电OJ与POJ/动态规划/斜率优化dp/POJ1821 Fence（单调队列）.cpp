/*
    设计状态f[i][j]表示前i人涂前j个，然后进行转移
    发现其中一部分可以通过单调队列维护降低复杂度
*/
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
const int N=1e5+7;
const int inf=0x3f3f3f3f;
int n,k;
struct node{
    int l,p,s;
}s[N];
int q[N];
int f[110][16100];
bool cmp(node a,node b){
    return a.s<b.s;
}
int main(){
    cin>>n>>k;
    int i;
    for(i=1;i<=k;i++){
      cin>>s[i].l>>s[i].p>>s[i].s;
    }
    sort(s+1,s+1+k,cmp);
    int j;
    memset(f,0,sizeof f);
    int hh=0;
    int tt=-1;
    for(i=1;i<=k;i++){
        hh=0;
        tt=0;
        q[0]=0;//队首0，当前唯一合法状态
        for(j=1;j<=n;j++){
            f[i][j]=max(f[i-1][j],f[i][j-1]);//该木匠不刷的情况
            if(j>=s[i].s+s[i].l)//涂不到但不能break，因为可能前面的工人也能涂到后面的板子
                continue;
            while(hh<=tt&&q[hh]+s[i].l<j)//当超过涂的范围就要除去
                hh++;
            if(j<s[i].s){//将可能的情况放入队列中
                int tmp=f[i-1][j]-s[i].p*j;
                while(hh<=tt&&f[i-1][q[tt]]-s[i].p*q[tt]<tmp)
                    tt--;
                q[++tt]=j;
                continue;
            }
            f[i][j]=max(f[i][j],f[i-1][q[hh]]+s[i].p*(j-q[hh]));
        }
    }
    cout<<f[k][n]<<endl;
}
