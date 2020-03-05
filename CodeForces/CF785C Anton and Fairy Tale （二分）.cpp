分析：
这道题本身比较简单，因为发现具有单调性，所以只需要枚举一下天数就行了
但是有个问题，这个数据直接算会爆long long ，我第一次就是直接枚举二分的
现在换一个思路，就是我们知道前m天肯定是放满的，所以只需要从m+1天开始枚举，在最后天数的时候在加上m
============================================
代码：
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<queue>
#include<map>
#include<cstring>
#include<string>
using namespace std;
typedef long  long ll;
ll n,m;
int main(){
    cin>>n>>m;
    ll l=1,r=INT_MAX;
    if(n<=m){
        cout<<n<<endl;
        return 0;
    }
    while(l<r){
        ll mid=l+r>>1;
        if(n-m<=(1+mid)*mid/2)
            r=mid;
        else
            l=mid+1;
    }
    cout<<l+m<<endl;
	return 0;
}
