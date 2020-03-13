分析：
这道题是典型的单调队列优化问题，题目虽然说得是交叉点，但是其实你可以把他看成格子，这也是常见技巧
之后你发现这就是求一个前缀和与前一行的值的相互关系，然后求最大值。大于指定长度的删掉
但是本题要注意的要求两遍，因为他可以往左也可以往右，并且注意不要忘记可以用0点更新。
此外，读入很严格，需要读入优化，以后做题感觉复杂度没错可以试试改变读入的方法
===================================
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
const int N=5e5+10;
const int inf=0x3f3f3f3f;
inline int read(){
    int x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}
int v[110][11000];
int len[110][11000];
int f[110][11000];
int q[N];
int main(){
    int i;
    int n,m,k;
    int j;
    while(scanf("%d%d%d",&n,&m,&k)){
        if(n==0&&m==0&&k==0)
            break;
        n++;
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                v[i][j]=read();
                v[i][j]+=v[i][j-1];
            }
        }
        memset(f,0,sizeof f);
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                len[i][j]=read();
                len[i][j]+=len[i][j-1];
            }
        }
        for(i=1;i<=n;i++){
            int hh=0;
            int tt=0;
            q[0]=0;
            for(j=1;j<=m;j++){
                while(hh<=tt&&f[i-1][j]-v[i][j]>f[i-1][q[tt]]-v[i][q[tt]])
                    tt--;
                q[++tt]=j;
                while(hh<=tt&&len[i][j]-len[i][q[hh]]>k)
                    hh++;
                f[i][j]=f[i-1][q[hh]]+v[i][j]-v[i][q[hh]];
            }
            hh=0;
            tt=0;
            q[0]=m;
            for(j=m;j>=0;j--){
                while(hh<=tt&&f[i-1][j]+v[i][j]>f[i-1][q[tt]]+v[i][q[tt]])
                    tt--;
                q[++tt]=j;
                while(hh<=tt&&len[i][q[hh]]-len[i][j]>k)
                    hh++;
                f[i][j]=max(f[i][j],f[i-1][q[hh]]+v[i][q[hh]]-v[i][j]);
            }
        }
        int res=-0x3f3f3f3f;
        for(i=1;i<=m;i++){
            res=max(f[n][i],res);
        }
        printf("%d\n",res);
    }
    return 0;
}
