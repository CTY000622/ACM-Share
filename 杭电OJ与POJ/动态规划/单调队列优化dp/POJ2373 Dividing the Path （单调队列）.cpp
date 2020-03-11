分析：
这道题细节较多，首先我们定义状态，f[i]表示处理到i的时候最小的个数，其实就是最后一个管的左边界，那么这些i都不能是奶牛所在的地方，因为我们枚举的是左边界
之后我们发现了单调性，其实就是取min+1，但是这个范围要在2a-2b之间，所以进队列的时候要小心
我这次犯的错是因为我把它当作以前的题目而没有发现这里的限制是必须是偶数的地方才有放，因为每个管子的范围都是偶数。
===============================================
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
const int N=1e6+7;
const int inf=0x3f3f3f3f;
int st[N];
struct node{
    int l,r;
}s[N];
int f[N];
int q[N];
int main(){
    int i;
    int n,m;
    int l,a,b;
    cin>>n>>l>>a>>b;
    for(i=1;i<=n;i++){
        cin>>s[i].l>>s[i].r;
        for(int j=s[i].l+1;j<s[i].r;j++)
            st[j]=1;
    }
    memset(f,0x3f,sizeof f);
    f[0]=0;
    int j;
    int hh=0;
    int tt=0;
    q[0]=0;
    for(int i=2*a;i<=l;i+=2){
       while(hh<=tt&&q[hh]<i-2*b)
          hh++;
       while(hh<=tt&&f[q[tt]]>=f[i-2*a])
          tt--;
       q[++tt]=i-2*a;
       if(st[i])
        continue;
       f[i]=f[q[hh]]+1;
    }
    if(f[l]<inf/2)
        cout<<f[l]<<endl;
    else
        cout<<-1<<endl;
}
