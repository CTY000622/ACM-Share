解析：
本题我们首先很容易可以列出朴素的状态和转移方程
f[i][j],代表前i个分j次购买的最小值
那么显然，这个值可以根据j-1次的所有结果更新而来，但这样的算法是n^2的，不过这题数据范围好像不太大
因为我是专题训练，所以我直接用上了斜率优化的方法
因为题目的转移方程是 f[i][x]=min(f[j][x-1]+max(p[j+1-i])*(s[i]-s[j]+10))
值得高兴的是，因为题目所给的价格是递增的，所以其中的max项就是p[i]，这样我们观察就能发现一些奇妙的地方
我们假设k<j,  如果f[k][x-1]+max(p[k+1-i])*(s[i]-s[k]+10)>=f[j][x-1]+max(p[j+1-i])*(s[i]-s[j]+10)
那么k显然是是不如j的，用代数法移项
就变成了 f[j][x-1]-f[k][x-1]/s[j]-s[k]<=p[i]
我们又发现p[i]是不断递增的，所以这个式子一旦满足则永远满足，因此可以从头部删除
而根据凸包优化原理，我们也可以证明从尾部删除的正确性，这道题的代码就出来了
======================================================================
代码：
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector> 
using namespace std;
const int N=1100;
int a[N];
int q[N]; 
int s[N];
int p[N];
int f[N][N];
int getup(int j,int i,int x){
    return f[i][x-1]-f[j][x-1];
}
int getdown(int j,int i){
    return s[i]-s[j];
}
int getdp(int j,int i,int x){
    return f[j][x-1]+p[i]*(s[i]-s[j]+10);
}
int main(){    
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        memset(s,0,sizeof s);
        memset(f,0,sizeof f);
        int i;
        for(i=1;i<=n;i++){
            scanf("%d%d",&a[i],&p[i]);
            s[i]=s[i-1]+a[i];
        }
        for(i=1;i<=n;i++)
        f[i][0]=(s[i]+10)*p[i];
        int x;
        int tt=0;
        int hh=0;
        for(x=1;x<=n-1;x++){
            tt=0;
            hh=0;
            q[0]=x;
            for(i=x+1;i<=n;i++){
                while(hh+1<=tt&&getup(q[hh],q[hh+1],x)<=p[i]*getdown(q[hh],q[hh+1]))
                hh++;
                f[i][x]=getdp(q[hh],i,x);
                while(hh+1<=tt&&getup(q[tt-1],q[tt],x)*getdown(q[tt],i)>=getdown(q[tt-1],q[tt])*getup(q[tt],i,x))
                tt--;
                q[++tt]=i;
            }
        }
        int res=0x3f3f3f3f;
        for(i=0;i<n;i++){
            res=min(res,f[n][i]);
        }
        cout<<res<<endl;
    }
    return 0;
}
