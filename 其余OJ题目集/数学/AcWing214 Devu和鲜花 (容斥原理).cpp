分析：
经典容斥原理，这其实是离散数学解不定方程或者高中组合数学的隔板法。
原问题可以转换为 x1+x2+x3+...xn=M+N;
又因为每个都有限制需要<=a[i]，因此我们可以反向考虑，总数-不合法数
而不合法数是所有>a[i]的合集，因此可以用容斥原理拆分，这里可以用二进制的表示方法表示取哪几个。
代码中还有其他细节：
请注意一定要防止爆int或者爆ll，随时取模+观察
==============================================
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
const int N=1e5+10;
const int mod=1e9+7;
ll n,m;
ll s[N];
int down=1;
int qmi(int a,int k){
    int res=1;
    while(k){
        if(k&1)
        res=(ll)res*a%mod;
        a=(ll)a*a%mod;
        k>>=1;
    }
    return res;
}
int C(ll a,ll b){
    if(a<b) //有可能存在减去数量很多的花导致要求的a小于b，那么这种情况是不存在的，所以返回0; 
    return 0;
    ll i;
    int up=1;
    for(i=a;i>a-b;i--){
        up=(i%mod*up%mod)%mod;
    }
    return (ll)up*down%mod;
}
int main(){
   cin>>n>>m;
   int i;
   for(i=0;i<n;i++)
   cin>>s[i];
   for(i=1;i<=n-1;i++)
   down=(ll)down*i%mod;
   down=qmi(down,mod-2);
   int res=0;
   for(i=0;i<1<<n;i++){
       ll a=m+n-1,b=n-1;
       int sign=1;
       for(int j=0;j<n;j++){
           if(i>>j&1){
               sign*=-1;
               a-=s[j]+1;//这+1是因为我们在求隔板的时候都要求至少有一个，而-s[j]会有取0的情况 
           }
       }
       res=(res+sign*C(a,b))%mod;
   }
   cout<<(res+mod)%mod<<endl;
}
