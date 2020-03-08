分析：
男人八题中的签到题，因为懒得用单调队列优化，所以用了二进制优化，但是这样很卡时限
我第一次是用int数组来表示dp数组，然后通过01背包的加法求，之后判断，但是这样memset的时间会很长，所以建议用bool数组+或判断，因为我们只在乎是否存在而不在乎多少
=======================================
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
const int N=1e5+7;
const int inf=0x3f3f3f3f;
int a[110],b[110];
int n,m;
int num[N];
bool f[N];
int main(){
    while(cin>>n>>m){
    if(n==0||m==0)
    break;
    int i;
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(i=1;i<=n;i++)
        scanf("%d",&b[i]);
    int cnt=0;
    for(i=1;i<=n;i++){
        int k=1;
        while(k<=b[i]){
            num[++cnt]=a[i]*k;
            b[i]-=k;
            k<<=1;
        }
        if(b[i]){
            num[++cnt]=a[i]*b[i];
        }
    }
    int j;
    memset(f,0,sizeof f);
    f[0]=1;
    for(i=1;i<=cnt;i++){
        for(j=m;j>=num[i];j--){
            f[j]|=f[j-num[i]];
        }
    }
    int res=0;
    for(i=1;i<=m;i++){
        if(f[i])
            res++;
    }
    printf("%d\n",res);
    }

}
