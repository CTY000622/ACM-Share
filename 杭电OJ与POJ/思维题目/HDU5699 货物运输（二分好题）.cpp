分析：
这道题相当精彩。推荐一个博文
https://blog.csdn.net/tc_to_top/article/details/51476095
另外还有几个坑点
1.需要特判相等的情况竟然还有相加为奇数不符合条件的情况
我连二分的判断条件都想不到，这个想法太缜密了
可见遇到题目需要思考性质，例如本题要求最大值的最小值，如果看出这一点就能做出答案
而看出这一点则需要发现最小值是因为他要求时间要小，但是要枚举最长的距离判断是否满足条件
======================================================
代码：
#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1e6+10;
int n,m;
int a[N];
int b[N];
int check(int x){
    int i;
    int ma1=0,ma2=0,mi1=0x3f3f3f3f;
    int mi2=0x3f3f3f3f;
    for(i=1;i<=m;i++){
        if(b[i]-a[i]>x){
            ma1=max(ma1,a[i]+b[i]-x);
            mi1=min(mi1,a[i]+b[i]+x);
            ma2=max(ma2,b[i]-a[i]-x);
            mi2=min(mi2,b[i]-a[i]+x);
        }
    }
    if(mi1>=ma1&&mi2>=ma2){
        if(mi1==ma1&&mi2==ma2){
            if((ma1+ma2)%2)
                return false;
        }
        return true;
    }
    return false;
}
int main(){
    while(cin>>n>>m){
    int i;
    for(i=1;i<=m;i++){
        scanf("%d%d",&a[i],&b[i]);
        if(a[i]>b[i])
            swap(a[i],b[i]);
    }
    int l=0,r=n;
    while(l<r){
        int mid=l+r>>1;
        if(check(mid))
            r=mid;
        else
            l=mid+1;
    }
    cout<<l<<endl;}
	return 0;
}
