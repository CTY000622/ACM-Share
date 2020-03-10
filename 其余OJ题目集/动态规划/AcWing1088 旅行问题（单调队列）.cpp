分析：
这道题有多种解法，这里介绍一种单调队列的写法
首先我们可以破环成链，这也是环形问题的一种思路
其次我们发现，我们可以用油量-路程来表示点的权值，替代点和边结合的权值。这样我们发现就是找前面前缀和的最大值来判断能否到达
因为可以走两个方向，所以要都做一遍
那么这里顺时针走需要倒着枚举，因为我们想要求的是s[j]-s[i]的值，从每个点出发的s[i]在那个时候都是固定的，所以我们需要找的是s[j]的最小值，所以要用到后面的信息
而逆时针走的时候要顺序枚举，因为我们要找s[i]的最大值，这里用到的是前面的信息
======================================
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
const int N=2e6+7;
const int inf=0x3f3f3f3f;
int p[N],d[N];
ll s[N];
int n;
int q[N];
int ans[N];
int main(){
    cin>>n;
    int i;
    for(i=1;i<=n;i++){
        scanf("%d%d",&p[i],&d[i]);
    }
    for(i=1;i<=n;i++)
        s[i]=s[i+n]=p[i]-d[i];
    for(i=1;i<=2*n;i++)
        s[i]+=s[i-1];
    int hh=0;
    int tt=0;
    q[0]=2*n+1;
    for(i=2*n;i;i--){
        if(q[hh]>i+n)
            hh++;
        if(i<n){
            if(s[q[hh]]-s[i]>=0)
                ans[i+1]=1;
        }
        while(hh<=tt&&s[q[tt]]>=s[i])
            tt--;
        q[++tt]=i;
    }
    hh=0;
    tt=0;
    q[0]=0;
    d[0]=d[n];
    for(i=1;i<=n;i++)
        s[i]=s[i+n]=p[i]-d[i-1];
    for(i=1;i<=2*n;i++)
        s[i]+=s[i-1];
    for(i=1;i<=2*n;i++){
        if(q[hh]<i-n)
            hh++;
        if(i>n){
            if(s[i]-s[q[hh]]>=0){
                ans[i-n]=1;
            }
        }
        while(hh<=tt&&s[q[tt]]<=s[i])
            tt--;
        q[++tt]=i;
    }
    for(i=1;i<=n;i++){
        if(ans[i])
            cout<<"TAK"<<endl;
        else
            cout<<"NIE"<<endl;
    }
    return 0;
}
