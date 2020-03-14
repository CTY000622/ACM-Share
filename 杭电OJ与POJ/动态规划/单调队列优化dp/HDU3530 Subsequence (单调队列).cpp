分析：
维护两个单调队列一个递增一个递减
如果两个差值大于l，那么把位置小的往后移，因为这样才能保证合法，不然比如最大值在1处，最小值在2处，现在我们移动最小值是不可能的，因为最小值始终在最大值和右端点的中间，无法移动，只能移动最大值，那么注意的是，如果移动后合法，那么当前的有效区间跟移动后在哪无关，其实是原先的地方+1，下面我们来举个例子
假如最大值在1处 最小值在3处且不满足条件，那么就找次大值，变成新的最大值假如在4处，那么有效区间是从2开始的，与3和4无关。
本题在做第三个比大小关系的时候无需判断队列是否为空，因为当前数永远存在，所以队列不可能为空。
===========================================
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
const int N=1e6+10;
const int inf=0x3f3f3f3f;
int q1[N];
int q2[N];
int a[N];
int main(){
    int i;
    int n,m,k;
    while(cin>>n>>m>>k){
        for(i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        int hh1=0;
        int tt1=-1;
        int hh2=0;
        int tt2=-1;
        int pos=0;
        int ans=0;
        for(i=1;i<=n;i++){
            while(hh1<=tt1&&a[q1[tt1]]<=a[i])
                tt1--;
            q1[++tt1]=i;
            while(hh2<=tt2&&a[q2[tt2]]>=a[i])
                tt2--;
            q2[++tt2]=i;
            while(a[q1[hh1]]-a[q2[hh2]]>k){
                if(q1[hh1]<q2[hh2]){
                    pos=q1[hh1++];
                }
                else{
                    pos=q2[hh2++];
                }
            }
            if(a[q1[hh1]]-a[q2[hh2]]>=m){
                ans=max(ans,i-pos);
            }
        }
        cout<<ans<<endl;
    }
}
