分析：
分析可以设置二维的dp状态i天有j块钱的最大收益
对w+1天之前的每天进行初始化，因为在这个时候只能买，也可以不买，但是这个不买在后面进行集体操作
之后就有3种情况，一种是买，一种是不操作，一种卖出
并且只有当满足条件的时候才能进行买卖，那么这个优化方法就明显了，不买的情况就是等于前一天这个钱的大小在满足条件的情况下找到收益最大的地方转移
而这里只需要用i-w-1进行转移就行了，为什么呢？
因为题目虽然说我们可以相隔w天以上都行，但是其实我们在进行单调队列操作的时候已经做了重要的一步，也就是f[i][j]=f[i-1][j]和fij的最大值，这也就说明相隔w+1天以上的值都已经通过这个操作转移过来了，也就是说如果在w+2天操作更好
那么这个值就会通过w+1天不操作转移过了，所以我们就可以直接操作i-w-1，因为这样如果w+2更优，其实就在对w+2天进行操作。
=====================================================
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
const int N=5e5+10;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
int a[N],b[N],c[N],d[N];
int q[N];
int f[2200][2200];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,maxp,w;
        cin>>n>>maxp>>w;
        int i;
        for(i=1;i<=n;i++){
            cin>>a[i]>>b[i]>>c[i]>>d[i];
        }
        int hh=0;
        int tt=-1;
        memset(f,-0x3f,sizeof f);
        f[0][0]=0;
        int j;
        for(i=1;i<=w+1;i++){
            for(j=0;j<=c[i];j++)
                f[i][j]=-a[i]*j;
        }
        for(i=1;i<=n;i++){
            hh=0;
            tt=-1;
            for(j=0;j<=maxp;j++)
                f[i][j]=max(f[i][j],f[i-1][j]);
            if(i<=w+1)
                continue;
            for(j=0;j<=maxp;j++){
                int tmp=f[i-w-1][j]+j*a[i];
                while(hh<=tt&&f[i-w-1][q[tt]]+q[tt]*a[i]<=tmp)
                    tt--;
                q[++tt]=j;
                while(hh<=tt&&q[hh]+c[i]<j)
                    hh++;
                f[i][j]=max(f[i][j],f[i-w-1][q[hh]]-(j-q[hh])*a[i]);
            }
            hh=0;
            tt=-1;
            for(j=maxp;j>=0;j--){
                int tmp=f[i-w-1][j]+j*b[i];
                while(hh<=tt&&f[i-w-1][q[tt]]+q[tt]*b[i]<=tmp)
                    tt--;
                q[++tt]=j;
                while(hh<=tt&&q[hh]-d[i]>j)
                    hh++;
                f[i][j]=max(f[i][j],f[i-w-1][q[hh]]+(q[hh]-j)*b[i]);
            }
        }
        int res=-0x3f3f3f3f;
        for(i=0;i<=maxp;i++){
            res=max(res,f[n][i]);
        }
        cout<<res<<endl;
    }
}
