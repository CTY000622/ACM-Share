一道很老的斜率优化dp
斜率优化看上去很难，其实是有技巧的 。
对于dp题目，如果你想优化他，一定要先列出朴素的表达式并观察性质
对于本题我们可以发现，如果要更新dp[i],我们就要从前面找到dp[j]+(s[i]-s[j])^2+m的最小值，其中s是前缀和
我们就可以猜测，一定有很多不可能转移的内容，我们应该如何删除它从而降低复杂度。
那么我们假设k<j，当i出现之后，k就不可能作为答案，那么这些k在i处满足的性质就是
dp[j]+(s[i]-s[j])^2+m<=dp[k]+(s[i]-s[k])^2+m
对这个式子进行化简移向，我们就可以得到一个式子
dp[j]+s[j]^2-(dp[k]+s[k]^2)/(2*(s[j]-s[k]))<=s[i]
为什么我们会想到这样移向？因为常见的优化就只有几种，例如四边形优化，单调队列优化，斜率优化，这个初始的式子中有两个变量，还是成对出现的
我们就可以猜测可以表达成斜率，当然这也是一种经验。
所以满足这个情况的k是不满足的当前i的
其次，我们注意到随着i的增长，s[i]是越来越大的，因此这个k永远都不会用到。
这是从头部删除，我们知道，斜率优化还有从尾部删除的，这些都有一种特定的公式，就是倒数第二条斜率比倒数第一条要大，也叫做凸包优化。
我们肯定想不出这样的技巧，但是前人的经验告诉我们这个就是斜率优化的凸包优化的技巧，所以我们应当记住这个结论，并对每个题分析证明这个结论在该题也成立
下面我们来分析，我们不妨记上面的公式为g[k,j]
对于新加入的i，如果g[k,j]>g[j,i]我们需要证明j永远用不到
1.假设g[j,i]<=s[i]，根据我们上面推出来的公式，j可以删除
2.g[j,i]>=s[i],那么g[k,j]>s[i]j依旧不会成为答案，因为k比j更适合
所以我们成功证明
下面就是套斜率板子就行。
本题题解借鉴了kuangbin的题解（思路都是kuangbin老师的），我写下为了自我学习，也为了给刚学习斜率优化的同学一点斜率的技巧。
====================================================================================================================
#include<cstdio>
#include<iostream>
#include<string>
#include<queue>
using namespace std;
const int N=500010;
int dp[N];
int q[N];
int sum[N];
int hh,tt,n,m;
int cal(int i,int j){
    return dp[j]+m+(sum[i]-sum[j])*(sum[i]-sum[j]);
}
int check(int j,int k){
    return dp[j]+sum[j]*sum[j]-(dp[k]+sum[k]*sum[k]);
}
int get(int j,int  k){
    return 2*(sum[j]-sum[k]);
}
int main(){

    while(cin>>n>>m){
        for(int i=1;i<=n;i++)
           scanf("%d",&sum[i]);
        sum[0]=dp[0]=0;
        for(int i=1;i<=n;i++)
           sum[i]+=sum[i-1];
        hh=tt=0;
        q[0]=0;
        for(int i=1;i<=n;i++){
            while(hh+1<=tt&&check(q[hh+1],q[hh])<=sum[i]*get(q[hh+1],q[hh]))
               hh++;
            dp[i]=cal(i,q[hh]);
            while(hh+1<=tt&&check(i,q[tt])*get(q[tt],q[tt-1])<=check(q[tt],q[tt-1])*get(i,q[tt]))
                    tt--;
            q[++tt]=i;
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
