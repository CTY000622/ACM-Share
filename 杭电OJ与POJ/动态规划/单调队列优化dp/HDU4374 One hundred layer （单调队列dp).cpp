分析：
这道题和之前poj的一道题目有着异曲同工之妙
所以也是考虑一个单调队列维护，首先对第一层进行初始化
这里有个小坑点就是，一行最多move t次，其实我们可以获得t+1个位置的数。因为从上面跳下来不算一次。
这样就可以通过前缀和乱搞了
单调队列本身很简单，就是处理边界问题的时候十分麻烦，需要谨慎处理
另外，本题有多组输入，题目提示的不是特别明显。
============================================
代码:
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
int f[110][11000];
int q[N];
int v[110][11000];
int s[110][11000];
int a[110][11000];
int main(){
    int i;
    int n,m,x,t;
    while(cin>>n>>m>>x>>t){
            memset(s,0,sizeof s);
    for(i=1;i<=n;i++){
    int j;
    for(j=1;j<=m;j++){
        scanf("%d",&a[i][j]);
        s[i][j]=s[i][j-1]+a[i][j];
        }
    }
    int j;
    int hh=0;
    int tt=-1;
    memset(f,-0x3f,sizeof f);
    f[1][x]=a[1][x];
    for(i=1;i<=x-1;i++){
        if(x-i<=t)
            f[1][i]=s[1][x]-s[1][i-1];
    }
    for(i=x+1;i<=m;i++){
        if(i-x<=t)
            f[1][i]=s[1][i]-s[1][x-1];
    }
    for(i=2;i<=n;i++){
        hh=0;
        tt=-1;
        for(j=1;j<=m;j++){
            int tmp=f[i-1][j]-s[i][j-1];
            while(hh<=tt&&f[i-1][q[tt]]-s[i][q[tt]-1]<=tmp)
                tt--;
            q[++tt]=j;
            while(hh<=tt&&q[hh]+t<j)
                hh++;
            f[i][j]=max(f[i][j],f[i-1][q[hh]]+(s[i][j]-s[i][q[hh]-1]));
        }
        hh=0;
        tt=-1;
        for(j=m;j>=1;j--){
            int tmp=f[i-1][j]+s[i][j];
            while(hh<=tt&&f[i-1][q[tt]]+s[i][q[tt]]<=tmp)
                tt--;
            q[++tt]=j;
            while(hh<=tt&&q[hh]-t>j)
                hh++;
            f[i][j]=max(f[i][j],f[i-1][q[hh]]-(s[i][j-1]-s[i][q[hh]]));
        }
   }
    int res=-0x3f3f3f3f;
    for(i=1;i<=m;i++){
        res=max(res,f[n][i]);
    }
    cout<<res<<endl;}
}
