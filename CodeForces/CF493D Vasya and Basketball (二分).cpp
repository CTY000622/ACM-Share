分析：
对于本题，因为数据，不难想到是nlogn左右的算法
本题的数据具有单调性，在排序之后，一定是以分界线为边，一边是2分一边是3分
我们可以暴力枚举分界线，并且根据分界线二分求得左右，之后计算最小
我们知道，分界线的种类只需要枚举a中所有数以及b中所有数再加上0的位置和无穷大的位置就可以表述所有情况
===============================================
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
const int N=2e5+10;
ll n;
int a[N];
int b[N];
ll m;
ll ans1;
ll ans2;
ll res1;
ll res2;
int res;
int main(){
    int i;
    cin>>n;
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    sort(a,a+n);
    cin>>m;
    for(i=0;i<m;i++){
        scanf("%d",&b[i]);
    }
    sort(b,b+m);
    res1=2*n;
    res2=2*m;
    ans1=res1;
    ans2=res2;
    res=res1-res2;
    res1=3*n;
    res2=3*m;
    int tmp=res1-res2;
    if(tmp>=res){
        res=tmp;
        ans1=res1;
        ans2=res2;
    }
    for(i=0;i<n;i++){
        int sign1=upper_bound(a,a+n,a[i])-a;
        int sign2=upper_bound(b,b+m,a[i])-b;
        res1=3*n-sign1;
        res2=3*m-sign2;
        if(res1-res2>res){
            res=res1-res2;
            ans1=res1;
            ans2=res2;
        }
        else if(res1-res2==res){
            if(res1>ans1){
            res=res1-res2;
            ans1=res1;
            ans2=res2;
            }
        }
    }
    for(i=0;i<m;i++){
        int sign1=upper_bound(a,a+n,b[i])-a;
        int sign2=upper_bound(b,b+m,b[i])-b;
        res1=3*n-sign1;
        res2=3*m-sign2;
        if(res1-res2>res){
            res=res1-res2;
            ans1=res1;
            ans2=res2;
        }
        else if(res1-res2==res){
            if(res1>ans1){
            res=res1-res2;
            ans1=res1;
            ans2=res2;
            }
        }
    }
    cout<<ans1<<":"<<ans2<<endl;
	return 0;
}
