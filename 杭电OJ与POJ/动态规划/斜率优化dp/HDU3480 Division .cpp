斜率dp的做法很单一，只要看出乘法就可以做，并且本题所以数据都是正数，所以可以做成线性复杂度
注意的是，我们在初始化队头的时候，要插入x-1的位置，因为更新的起点不能比第二维的要小
==============================================================================
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>
#include<string>
#include<cstring>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
const int N=1e4+10;
int a[N];
int f[N][5050];
int q[N];
int getdp(int j,int i,int x){
    return f[j][x-1]+a[i]*a[i]-2*a[i]*a[j+1]+a[j+1]*a[j+1];
}
int getup(int k,int j,int x){
    return f[j][x-1]+a[j+1]*a[j+1]-(f[k][x-1]+a[k+1]*a[k+1]);
}
int getdown(int j,int i){
    return a[i+1]-a[j+1];
}
int main(){
    int t;
    cin>>t;
    int cnt=1;
    while(t--){
        int n;
        int i;
        int m;
        cin>>n>>m;
        for(i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        sort(a+1,a+1+n);
        memset(f,0x3f,sizeof f);
        f[0][0]=0;
        for(i=1;i<=n;i++){
            f[i][1]=(a[i]-a[1])*(a[i]-a[1]);
        }
        int x;
        int j;
        for(x=2;x<=m;x++){
            int tt=0;
            int hh=0;
            q[0]=x-1;
            for(i=x;i<=n;i++){
                while(hh+1<=tt&&getup(q[hh],q[hh+1],x)<=2*a[i]*getdown(q[hh],q[hh+1]))
                hh++;
                f[i][x]=getdp(q[hh],i,x);
                while(hh+1<=tt&&getup(q[tt-1],q[tt],x)*getdown(q[tt],i)>=getup(q[tt],i,x)*getdown(q[tt-1],q[tt]))
                tt--;
                q[++tt]=i;
            }
        }
        printf("Case %d: %d\n",cnt++,f[n][m]);
    } 
}
